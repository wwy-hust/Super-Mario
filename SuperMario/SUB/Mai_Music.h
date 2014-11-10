/* Music */

Mai_Status Mai_DFT0(Mai_I16* src, Mai_I32 num_s, Mai_I32_Fixed1* dst, Mai_I32* num_d);


/* Mai_MusicStream */
class Mai_MusicStream
{
public:
	virtual ~Mai_MusicStream() {};
	virtual Mai_I32 getFormat() = 0;
	virtual Mai_I32 getNumChannels() = 0;
	virtual Mai_I32 getSampleRate() = 0;
	virtual Mai_I32 getBitsPerSingleSample() = 0;
	virtual Mai_I32 getSampleNum() = 0;
	virtual Mai_I32 getCurrentBitrate() = 0;
	virtual Mai_I32 moreSamples(Mai_I8* samples, Mai_I32 samplenum_to_get) = 0;
	virtual Mai_Status seekSample(Mai_I32 sample) = 0;
	virtual Mai_I32 getSample() = 0;
	virtual Mai_I32 getStatus() = 0;
	virtual Mai_Status close() = 0;
};

/* Mai_Wav */
class Mai_Wav:public Mai_MusicStream
{
private:
	RandomAccessFile* src;
	Mai_Status status;

	Mai_I64 ChunkSize;

	Mai_I32 samplenum;
	Mai_I32 sample_now;

	Mai_I32 AudioFormat;
	Mai_I32 NumChannels;
	Mai_I32 SampleRate;
	Mai_I64 ByteRate;
	Mai_I32 BlockAlign;
	Mai_I32 BitsPerSample;

	Mai_I64 stream_size;
	Mai_I64 stream_start_pointer;

	Mai_Bool is_active;

public:
	Mai_Wav(RandomAccessFile* raf0);
	Mai_I32 getFormat();
	Mai_I32 getNumChannels();
	Mai_I32 getSampleRate();
	Mai_I32 getBitsPerSingleSample();
	Mai_I32 getStatus();
	Mai_I32 getSample();
	Mai_I32 getSampleNum();
	Mai_I32 getCurrentBitrate();
	Mai_I32 moreSamples(Mai_I8* samples, Mai_I32 samplenum_to_get);
	Mai_Status seekSample(Mai_I32 sample);
	Mai_Status close();
	~Mai_Wav();
};

/* Mai_Mp3 */
class Mai_Mp3:public Mai_MusicStream
{
private:
	RandomAccessFile* src;
	Mai_Status status;
private:
	Heap_Alloc0 heap0;
private:
	Mai_I32 start_location;
	Mai_I32 end_location;
	Mai_I32 side;
	Mai_I32 padding;
	Mai_I32 frame_size;
private:
	Mai_I32 sample_now;
private:
	struct struct_buffer
	{
		Mai_I8 *head;
		Mai_I32 length;
	} buffer;

	struct
	{
		int frame_num;
		int is_toc;
		int toc[100];
	} info;

	Mai_Void *header0;
	Mai_Void *stream0;

	Mai_Void *frame0;
	Mai_Void *synth0;

private:
	Mai_I32 CurrentBitrate;

private:
	Mai_I32 getFrameSize(Mai_Void *mhd0, Mai_I8 *head);
	Mai_I32 getInt(Mai_I8 *head);
	Mai_I32 getXing(Mai_I8 *head, Mai_I32 length);
	Mai_I32 Seach_FF(Mai_I8 *head, Mai_I32 length);
public:
	Mai_Mp3(RandomAccessFile* raf0);
	Mai_I32 getFormat();
	Mai_I32 getNumChannels();
	Mai_I32 getSampleRate();
	Mai_I32 getBitsPerSingleSample();
	Mai_I32 getSampleNum();
	Mai_I32 getStatus();
	Mai_I32 getSample();
	Mai_I32 getCurrentBitrate();
	Mai_I32 moreSamples(Mai_I8* samples, Mai_I32 samplenum_to_get);
	Mai_Status seekSample(Mai_I32 sample);
	Mai_Status close();
};

/* Mai_TTA */
class Mai_TTA:public Mai_MusicStream
{
public:
	RandomAccessFile* src;
private:
	Mai_Status status;

	Mai_I32 samplenum;
	Mai_I32 sample_now;

	Mai_I32 AudioFormat;
	Mai_I32 NumChannels;
	Mai_I32 SampleRate;
	//Mai_I64 ByteRate;
	//Mai_I32 BlockAlign;
	Mai_I32 BitsPerSample;

private:
	Mai_Void* tta_callback;
	Mai_Void* decoder0;
private:
	Heap_Alloc0 heap0;
public:
	Mai_TTA(RandomAccessFile* raf0);
	Mai_I32 getFormat();
	Mai_I32 getNumChannels();
	Mai_I32 getSampleRate();
	Mai_I32 getBitsPerSingleSample();
	Mai_I32 getStatus();
	Mai_I32 getSample();
	Mai_I32 getSampleNum();
	Mai_I32 getCurrentBitrate();
	Mai_I32 moreSamples(Mai_I8* samples, Mai_I32 samplenum_to_get);
	Mai_Status seekSample(Mai_I32 sample);
	Mai_Status close();
	~Mai_TTA();
};

/* Mai_APE */
class Mai_APE:public Mai_MusicStream
{
public:
	RandomAccessFile* src;
private:
	Mai_Status status;

	Mai_I32 samplenum;
	Mai_I32 sample_now;

	Mai_I32 AudioFormat;
	Mai_I32 NumChannels;
	Mai_I32 SampleRate;
	//Mai_I64 ByteRate;
	//Mai_I32 BlockAlign;
	Mai_I32 BitsPerSample;
	Mai_I32 CurrentBitrate;

private:
	Mai_Void* decoder0;
	Mai_Void* io_handle;

private:
	Heap_Alloc0 heap0;
public:
	Mai_APE(RandomAccessFile* raf0);
	Mai_I32 getFormat();
	Mai_I32 getNumChannels();
	Mai_I32 getSampleRate();
	Mai_I32 getBitsPerSingleSample();
	Mai_I32 getStatus();
	Mai_I32 getSample();
	Mai_I32 getSampleNum();
	Mai_I32 getCurrentBitrate();
	Mai_I32 moreSamples(Mai_I8* samples, Mai_I32 samplenum_to_get);
	Mai_Status seekSample(Mai_I32 sample);
	Mai_Status close();
	~Mai_APE();
};

/* Mai_MusicControl */
class Mai_MusicControl:public MaiThread
{
private:
	WAVEFORMATEX wfx;
	DSBUFFERDESC dsbdesc;
	LPDIRECTSOUNDBUFFER pdsb;
	LPDIRECTSOUNDBUFFER8 pdsb8;
private:
	HWND hwnd0;
private:
	Mai_Bool is_active;
	Mai_Bool is_run;
	Mai_Bool is_run_in;
	Mai_Bool is_run_in2;
	Mai_Bool can_play;
	Mai_Bool is_inner_call;
	//Mai_Bool is_seek=false;
private:
	Mai_Bool f_is_loop;
private:
	Mai_MusicStream* stream0;
	Mai_Quene0* buffer0;
	Mai_I8* buffer_t;
	Mai_I32 buffer_t_s;
	Heap_Alloc0 heap0;
	Mai_I32 s_buffer_size;
	Mai_I32 s_buffer_off;
private:
	Mai_I32 dft_k;
	Mai_Quene0* buffer_dft;
	Mai_I8* buffer_dft_k;

public:
	class SBufferFiller:public MaiThread
	{
	private:
		Mai_MusicControl* mmc0;
	public:
		SBufferFiller(Mai_MusicControl* mmc);
		Mai_Status Proc();
	};
	friend class SBufferFiller;
	SBufferFiller* sbf0;
public:
	Mai_MusicControl(HWND hwnd);
	Mai_Status fillBuffer();
	Mai_Status fillSBuffer();
	Mai_Status Proc();
	Mai_Status Music_start(RandomAccessFile* raf0);
	Mai_Status Music_restart();
	Mai_Status Music_stop();
	Mai_I32 Music_getTime();
	Mai_I32 Music_getAllTime();
	Mai_I32 Music_getCurrentBitrate();
	Mai_Status Music_seek_time(Mai_I32 s_time);
	Mai_Status testDFT();
	Mai_Status setLoop(Mai_Bool is_loop = 1);

};

/* MaiCapture */
class MaiCapture : public MaiThread
{
private:
	Mai_I32 dft_k;
	Mai_Quene0* buffer_dft;
	Mai_I8* buffer_dft_k;

private:
	WAVEFORMATEX wfx;
	DSCBUFFERDESC dscbd;
	LPDIRECTSOUNDCAPTUREBUFFER8 pDSCB8;

private:
	Mai_Quene0 *mq0;
	//Mai_I8 *temp_b;
	Heap_Alloc0 heap0;

private:
	Mai_Bool is_ok;
	Mai_I32 off_cap;
	Mai_Bool is_over;
public:
	MaiCapture();
	~MaiCapture();
	Mai_Status Proc();
	Mai_Quene0 *getBuffer();
	Mai_Status testDFT(Mai_I32_Fixed *left, Mai_I32_Fixed *right);
};

#include <dshow.h>

/* MaiMixerLocker */
class MaiMixerLocker : public MaiThread
{
private:
	IBaseFilter *pSrc;
	Mai_I32 num_of_pins;
	IPin *ip0[10];
	struct
	{
		Mai_Bool is_pin_need;
		Mai_Bool is_pin_in;
		IAMAudioInputMixer *pPinMixer;
		Mai_WChar name[64];
	} mai_pins[10];

	Mai_Bool is_ok;
	Mai_Bool is_over;
public:
	MaiMixerLocker();
	~MaiMixerLocker();
	Mai_Status Proc();
};

/* MaiWAVWriter */
class MaiWAVWriter
{
private:
	RandomAccessFile* raf0;
	Mai_I64 stream_start_pointer;
public:
	MaiWAVWriter(RandomAccessFile* raf);
	~MaiWAVWriter();
	Mai_I32 write(Mai_Void* b, Mai_I32 off, Mai_I32 len);
};
