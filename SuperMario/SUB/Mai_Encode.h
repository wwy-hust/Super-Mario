class Mai_Sha1
{
private:
	static Mai_U32 exc(Mai_U32 src);
public:
	static Mai_I32_Fixed1 parc;
public:
	static Mai_Status encodeFile(Mai_U32* h, RandomAccessFile* src);
	static Mai_Status precalc(Mai_U32* w);
	static Mai_Status calc(Mai_U32* h_dst, Mai_U32* h_src, Mai_U32* w);
};