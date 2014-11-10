

/* Mai_CompressFile */
Mai_Status Mai_CompressFile(RandomAccessFile* dst, RandomAccessFile* src);

/* RandomAccessMaiFile */
class RandomAccessMaiFile
{
private:
	struct
	{
		Mai_I64 size;
		Mai_I64 pointer_of_search_table;
		Mai_I64 size_of_search_table_compressed;
	} file_head;
	struct
	{
		Mai_I64* table;
		Mai_I64 size;
	} search_table;
	Mai_I64 head_begin;
	Mai_I64 code_begin;
	Mai_Quene0* quene_in;
	Mai_Quene0* quene_out;
	Mai_Quene0* quene_buffer;
	Mai_I8* buffer;
	RandomAccessFile* raf0;
	Mai_Decompress* md0;
	Heap_Alloc0 heap0;
	Mai_I32 is_ok;

	Mai_I64 block_num;
	Mai_I64 file_pointer;
	Mai_I64 file_size;
private:
	Mai_Status moreBlock();
public:
	RandomAccessMaiFile(RandomAccessFile* src);
	Mai_Status seek(Mai_I64 pos);
	Mai_I64 getFilePointer();
	Mai_I64 length();
	Mai_I32 read(Mai_Void* b, Mai_I32 off, Mai_I32 len);
};



/*class RandomAccessMaiFile
{
private:
	struct
	{
		Mai_I32 size;
		Mai_I32 pointer_of_search_table;
		Mai_I32 size_of_search_table_compressed;
	} file_head;
	struct
	{
		Mai_I32* table;
		Mai_I32 size;
	} search_table;
	Mai_I32 head_begin;
	Mai_I32 code_begin;
	Mai_Quene0* quene_in;
	Mai_Quene0* quene_out;
	Mai_Quene0* quene_buffer;
	Mai_I8* buffer;
	RandomAccessFile* raf0;
	Mai_Decompress* md0;
	Heap_Alloc0 heap0;
	Mai_I32 is_ok;

	Mai_I32 block_num;
	Mai_I32 file_pointer;
	Mai_I32 file_size;
private:
	Mai_Status moreBlock();
public:
	RandomAccessMaiFile(RandomAccessFile* src);
	Mai_Status seek(Mai_I32 pos);
	Mai_I32 getFilePointer();
	Mai_I32 length();
	Mai_I32 read(Mai_Void* b, Mai_I32 off, Mai_I32 len);
};*/

