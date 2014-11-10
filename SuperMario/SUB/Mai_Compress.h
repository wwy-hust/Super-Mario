/* Mai_Quene0 */


/* BitMachineIn0 */
class BitMachineIn0
{
private:
	Mai_Quene0* quene_in;
	Mai_I32 buffer;
	Mai_I32 bits_num;
private:
	Mai_Status moreByte();
public:
	BitMachineIn0(Mai_Quene0* quene_in);
	Mai_Bool isEnd();
	Mai_I32 getBitsNum();
	Mai_I32 getBitsNumRemaining();
	Mai_I32 getWithI32Buffer(Mai_I32 bnum);
	Mai_I32 getWithI32BufferPre(Mai_I32 bnum);
};

/* BitMachineOut0 */
class BitMachineOut0
{
private:
	Mai_Quene0* quene_out;
	Mai_I32 buffer;
	Mai_I32 bits_num;
public:
	BitMachineOut0(Mai_Quene0* quene_out);
	Mai_Status flush0();
	Mai_Status flush(Mai_Bool is_pad = 1);
	Mai_Status putWithI32Buffer(Mai_I32 src, Mai_I32 bnum);
	Mai_Status putWithI64Buffer(Mai_I64 src, Mai_I32 bnum);
};

/* Mai_LZSS */
class Mai_LZSS
{
private:
	typedef struct _TableElem
	{
		Mai_I32 location;
		struct _TableElem* front;
		struct _TableElem* next;
	} TableElem;
	
	TableElem te0[256];
	TableElem **te1;

	typedef struct _Buffer
	{
		Mai_I8* base;
		Mai_I32 h;
		Mai_I32 h_to_scan;
		Mai_I32 size;
	} Buffer;

	Buffer inputbuffer;

	typedef struct
	{
		Mai_I64 code;
		Mai_I32 bits_num;
	} Mai_DisCode, Mai_LenCode;
	Mai_Bool is_ok;
	Mai_Bool is_end;
	Mai_Quene0* quene_in;
	Mai_Quene0* quene_out;
	Heap_Alloc0 heap0;

	TableElem* elem_now;

	Mai_I32 counter;

	Mai_I32 window_size;

	Mai_I32 best_len_check;

	BitMachineOut0* bmo0;
private:
	Mai_I32 cmp(Mai_I8* src0, Mai_I8* src1, Mai_I32 max_num);
	Mai_I32 getMin(Mai_I32 src0, Mai_I32 src1);
	Mai_I32 getDisBitsNum(Mai_I32 distance);
	Mai_I32 getLenBitsNum(Mai_I32 length);
	Mai_DisCode DisToCode(Mai_I32 distance);
	Mai_LenCode LenToCode(Mai_I32 length);
	Mai_Status clearSearchTable();
	Mai_Status clearSearchTable2();
	Mai_Status putLocation(Mai_I8 let, Mai_I32 location);
	Mai_Status delLocation(Mai_I8 let, Mai_I32 location);
	Mai_Status setSearchTableLet(Mai_I8 let);
	Mai_I32 nextSearchTableLetLocation();
	Mai_Status shiftNext(Mai_I32* tuke);
	Mai_Status shift(Mai_I32 num, Mai_I32* tuke);
public:
	Mai_LZSS(Mai_Quene0* quene_in);
	~Mai_LZSS();
	Mai_Quene0* getOutQuene();
	Mai_Status compress();
	Mai_Status setEnd();
	Mai_Status setNewWindowSize(Mai_I32 window_size);
};

/* Mai_Compress */
class Mai_Compress
{
private:
	Mai_I32 max_of_nodes;
	typedef struct _Node
	{
		Mai_I32 freq;
		Mai_I32 depth;
		Mai_I32 value;
		Mai_I32 code;
		struct _Node* father;
	} Node;
	struct
	{
		Node* head;
		Node** scan;
		Mai_I32 h1;
		Mai_I32 h2;
	} nodes;
	typedef struct
	{
		Mai_I32* buffer0;
		Mai_I32 h0;
		Mai_I32 size0;
		Mai_I32 max_size0;

		Mai_I32* buffer10;
		Mai_I32* buffer11;
		Mai_I32 h1;
		Mai_I32 size1;
		Mai_I32 max_size1;

		Mai_I32* buffer20;
		Mai_I32* buffer21;
	} LZData;
	Mai_LZSS* lz0;
	LZData lzd0;
	Mai_Quene0* quene_in;
	Mai_Quene0* quene_out;
	BitMachineIn0* bmi0;
	BitMachineOut0* bmo0;
	Heap_Alloc0 heap0;

	Mai_I32 is_ok;
private:
	Mai_Status decodeLZCode();
	Mai_Status getFraqs();
	Mai_Status putFraqNode(Node* in);
	Node* getMinFraqNode();
	Mai_Status getDepth();
	Mai_Status getCodes();
	Mai_I32 getMaxDepthBitsNum();
	Mai_Status outputDepth();
	Mai_Status outputCodes();
public:
	typedef struct _Cus
	{
		Mai_I32 max_of_nodes;
	} Cus;
public:
	Mai_Compress(Mai_Quene0* quene_in);
	~Mai_Compress();
	Mai_Quene0* getOutQuene();
	Mai_Status compress();
};

/* Mai_Decompress */
class Mai_Decompress
{
private:
	struct
	{
		Mai_I8* head;
		Mai_I32 size;
	} buffer;
	typedef struct _Node
	{
		Mai_I32 freq;
		Mai_I32 depth;
		Mai_I32 value;
		Mai_I32 code;
		struct _Node* father;
	} Node;
	struct
	{
		Node* head;
		Node** scan;
		Mai_I32 h1;
		Mai_I32 h2;
	} nodes;
	typedef struct _TableElem
	{
		Mai_I32 depth;
		Mai_I32 value;
		Mai_I32 table_num;
	} TableElem;
	struct
	{
		TableElem** table;
		Mai_I32 table_num;
	} search_table;
	Mai_I32 max_of_nodes;
	Mai_Quene0* quene_in;
	Mai_Quene0* quene_out;
	BitMachineIn0* bmi0;
	Heap_Alloc0 heap0;

	Mai_I32 is_ok;
private:
	Mai_Status getDepth();
	Mai_Status makeSearchTable();
public:
	Mai_Decompress(Mai_Quene0* quene_in);
	~Mai_Decompress();
	Mai_Quene0* getOutQuene();
	Mai_Status Decompress();
};
