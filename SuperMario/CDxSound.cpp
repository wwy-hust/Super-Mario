#include "CDxSound.h"

/************************************************************************/
/* 
/* 以下为CDxSound类成员函数的定义
/*                                                                     
/************************************************************************/
//构造函数
CDxSound::CDxSound()
{
	ds = 0;
}

//析构函数
CDxSound::~CDxSound()
{
	ReleaseAll();
}

//创建DirectSound对象、设置合作级别并创建主缓冲区
bool CDxSound::CreateDS(HWND hWnd, int freq)
{
	//创建DirectSound对象
	HRESULT result = DirectSoundCreate(NULL, &ds, NULL);
	if (FAILED(result)) return false;

	//设置DirectSound合作级别（优先级）
	result = ds->SetCooperativeLevel(hWnd, DSSCL_PRIORITY);
	if (FAILED(result))	return false;

	//创建DirectSound缓冲区
	return dsbuf.CreateMainBuffer(*this, freq);
}

//释放DirectSound对象及DirectSound缓冲区对象
void CDxSound::ReleaseAll()
{
	if (ds) {
		dsbuf.Release();
		ds->Release();
		ds = 0;
	}
}

//失去缓冲区内存时则复原
HRESULT CDxSound::RestoreAll()
{
	HRESULT result = dsbuf.Restore();
	if (result != DS_OK) return result;

	return DS_OK;
}

/************************************************************************/
/* 
/* 以下为CDxSoundBuffer类成员函数的定义
/*                                                                     
/************************************************************************/

//构造函数
CDxSoundBuffer::CDxSoundBuffer():SndBuf(0),Volume(0),Pan(0),Freq(0)
{	}

//析构函数
CDxSoundBuffer::~CDxSoundBuffer()
{
	if(SndBuf) SndBuf->Release();
}

//创建辅助缓冲区并设计基本属性
bool CDxSoundBuffer::CreateBuffer(CDxSound &ds, WAVEFORMATEX *format, int size)
{
	DSBUFFERDESC dsbd;
	//使用0填充dsbd内存快
	ZeroMemory(&dsbd, sizeof(dsbd));

	//设置dsbd属性值
	dsbd.dwSize = sizeof(dsbd);
	dsbd.dwFlags =	DSBCAPS_GETCURRENTPOSITION2| 
		DSBCAPS_GLOBALFOCUS| 
		DSBCAPS_CTRLPOSITIONNOTIFY| 
		DSBCAPS_CTRLVOLUME| 
		DSBCAPS_CTRLPAN| 
		DSBCAPS_CTRLFREQUENCY;
	dsbd.dwBufferBytes = size;
	dsbd.lpwfxFormat = format;

	//创建缓冲区
	HRESULT result = ds->CreateSoundBuffer(&dsbd, &SndBuf, NULL);
	if (FAILED(result)) return false;

	//获取缓冲区属性值并使用获取的值初始化相关变量
	SndBuf->GetVolume(&Volume);
	SndBuf->GetPan(&Pan);
	SndBuf->GetFrequency(&Freq);

	return true;
}

//创建主缓冲区并将主缓冲区设定为WAVE格式
bool CDxSoundBuffer::CreateMainBuffer(CDxSound &ds, int freq)
{
	DSBUFFERDESC dsbd;
	//使用0填充dsbd内存快
	ZeroMemory(&dsbd, sizeof(dsbd));

	//设置dsbd属性值
	dsbd.dwSize = sizeof(dsbd); 
	dsbd.dwFlags = DSBCAPS_CTRLVOLUME | 
		DSBCAPS_CTRLPAN | 
		DSBCAPS_PRIMARYBUFFER;//该标志表示要创建主缓冲区
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = NULL;

	//调用DirectSound对象创建主缓冲区
	HRESULT result = ds->CreateSoundBuffer(&dsbd, &SndBuf, NULL);
	if(FAILED(result)) return false;

	WAVEFORMATEX wfex;
	//使用0填充wfex内存快
	ZeroMemory(&wfex, sizeof(wfex));

	//设定WAVE格式对象属性
	wfex.wFormatTag = WAVE_FORMAT_PCM;
	wfex.nChannels = 2;
	wfex.nSamplesPerSec = freq;
	wfex.nBlockAlign = 4;
	wfex.nAvgBytesPerSec = wfex.nSamplesPerSec * wfex.nBlockAlign;
	wfex.wBitsPerSample = 16;

	//将缓冲区格式设置为WAVE文件格式
	result = SndBuf->SetFormat(&wfex);
	if(FAILED(result)) return false;

	//获取缓冲区属性值并使用获取的值赋给相关变量
	SndBuf->GetVolume(&Volume);
	SndBuf->GetPan(&Pan);
	SndBuf->GetFrequency(&Freq);

	return true;
}

//读入WAVE文件,并将文件数据写入缓冲区
bool CDxSoundBuffer::LoadWave(CDxSound &ds, const char *path)
{
	CWave file;
	if(!file.Open(path) || !file.StartRead()) return false;

	Release();		// 如果已经有缓冲区，就释放

	//使用WAVE文件大小建立缓冲区
	if(!CreateBuffer(ds, file.GetFormat(), file.CkSize()))
		return false;

	//将WAVE文件数据写入缓冲区
	void *ptr1, *ptr2;
	DWORD bytes1, bytes2;
	HRESULT result = SndBuf->Lock( 0, file.CkSize(), 
		&ptr1, &bytes1, 
		&ptr2, &bytes2, 0);
	//如果缓冲区丢失，则恢复，然后锁定并写入数据
	if(result == DSERR_BUFFERLOST) {
		Restore();
		result = SndBuf->Lock( 0, file.CkSize(), 
			&ptr1, &bytes1, 
			&ptr2, &bytes2, 0);
	}

	//写入成功后，解除锁定
	if(SUCCEEDED(result)) {
		bool readerror = false;
		DWORD nread;

		//判读是否存在错误
		if(!file.Read(bytes1, (LPBYTE)ptr1, &nread) || 
			bytes1 != nread)
			readerror = true;
		if(bytes2) 
		{
			if(!file.Read(bytes2, (LPBYTE)ptr2, &nread) || 
				bytes2 != nread)
				readerror = true;
		}

		//解除锁定
		result = SndBuf->Unlock(ptr1, bytes1, ptr2, bytes2);

		if(readerror) return false;

		return true;
	}

	return false;
}

//释放所有资源
HRESULT CDxSoundBuffer::Release()
{
	HRESULT result = DS_OK;
	if(SndBuf) result = SndBuf->Release();
	SndBuf = 0;
	return result;
}

//恢复缓冲区
HRESULT CDxSoundBuffer::Restore()
{
	HRESULT result = DS_OK;
	if(SndBuf) return SndBuf->Restore();
	return DS_OK;
}

/************************************************************************/
/* 
/* 以下为CWave成员函数的定义
/*                                                                     
/************************************************************************/
CWave::CWave():hmmio(0), wfex(0)
{	}

CWave::~CWave()
{
	Close();
}

//打开指定路径下的WAVE文件
bool CWave::Open(const char *path)
{
	//打开指定路径下的WAVE文件，并返回文件句柄
	hmmio = mmioOpen((char *)path, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if(hmmio == NULL)	return false;

	// 将文件数据移动到RIFF区块
	if(mmioDescend(hmmio, &ckInRIFF, NULL, 0) != 0)
		return false;

	//判断文件类型是否为是否为WAVE类型
	if((ckInRIFF.ckid != FOURCC_RIFF)||
		(ckInRIFF.fccType != mmioFOURCC('W', 'A', 'V', 'E')))
		return false;

	//搜索文件数据的fmt区块
	ckIn.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if(mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK) != 0)
		return false;

	//如果fmt区块小于PCMWAVEFORMAT，表示fmt区块太小
	if(ckIn.cksize < sizeof(PCMWAVEFORMAT)) return false;

	wfex = (WAVEFORMATEX *)new char[ckIn.cksize];
	if(wfex == 0)  return false;

	//将fmt区块读入wfex结构体
	if(mmioRead(hmmio, (HPSTR)wfex, ckIn.cksize) != (LONG)ckIn.cksize)
		return false;

	//操作完毕，跳出fmt区块
	if(mmioAscend(hmmio, &ckIn, 0) != 0) return false;

	return true;
}

//读取并查询是否存在data区块
bool CWave::StartRead()
{
	if(mmioSeek(hmmio, ckInRIFF.dwDataOffset + sizeof(FOURCC), SEEK_SET) == -1)
		return false;

	//搜索文件数据的data区块
	ckIn.ckid = mmioFOURCC('d', 'a', 't', 'a');
	//如果没有data区块
	if(mmioDescend(hmmio, &ckIn, &ckInRIFF, MMIO_FINDCHUNK) != 0)
		return false;			
	return true;
}

//读取指定数据
bool CWave::Read(unsigned long size, void *data, unsigned long *nread)
{
	*nread = 0;
	int result = mmioRead(hmmio, (HPSTR)data, size);
	if (result == -1) return false;
	*nread = (unsigned)result;
	return true;
}

//关闭文件
bool CWave::Close()
{
	delete[] (char *)wfex;
	wfex = 0;

	if(hmmio != NULL) 
		return mmioClose(hmmio, 0) == 0;

	return true;
}