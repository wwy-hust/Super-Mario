/* Mai_Lyric */
class Mai_Lyric
{
public:
	typedef struct _Word
	{
		WCHAR* data;
		Mai_I32 time_st;
		Mai_I32 time_ed;
		Mai_I32 frame_time_st;
		Mai_I32 frame_time_ed;
		Mai_I32_Fixed loc_x, loc_y;
	} Word;
	typedef struct _Line
	{
		Word* word;
		Mai_I32 n;
		Mai_I32 n_max;
	} Line;
	struct
	{
		Line* line;
		Mai_I32 n;
		Mai_I32 n_max;
	} lyric;

private:
	Heap_Alloc0 heap0;
	RandomAccessFile* raf0;
public:
	Mai_Lyric(RandomAccessFile* src);
	Mai_Status get();
	Mai_Status analyzeFrame(Mai_I32_Fixed1 fps = 1571291);
};

typedef struct _SubPicDesc
{
	Mai_I32 type;
	Mai_I32 w, h, bpp, pitch, pitchUV;
	Mai_Void* bits;
	Mai_U8* bitsU;
	Mai_U8* bitsV;
	//RECT vidrect; // video rectangle

	struct _SubPicDesc() {type = 0; w = h = bpp = pitch = pitchUV = 0; bits = NULL; bitsU = bitsV = NULL;}
} SubPicDesc;

/* Mai_Image */
class Mai_Image
{
public:
	#define Type_Default 0
	#define Type_YV12 1
private:
	struct
	{
		Mai_I32* data;
		Mai_I32 width;
		Mai_I32 height;
		Mai_I32 pitch;
		Mai_I32 type;
	} bitmap;
	Heap_Alloc0 heap0;

	Mai_I32 is_ok;
	Mai_Bool is_out_image;
private:
	Mai_U8 Clip_base[256*3];
	Mai_U8* Clip;

	Mai_I32 c2y_cyb;
	Mai_I32 c2y_cyg;
	Mai_I32 c2y_cyr;
	Mai_I32 c2y_cu;
	Mai_I32 c2y_cv;

	Mai_I32 c2y_yb[256];
	Mai_I32 c2y_yg[256];
	Mai_I32 c2y_yr[256];

	Mai_I32 y2c_cbu;
	Mai_I32 y2c_cgu;
	Mai_I32 y2c_cgv;
	Mai_I32 y2c_crv;

	Mai_I32 y2c_bu[256];
	Mai_I32 y2c_gu[256];
	Mai_I32 y2c_gv[256];
	Mai_I32 y2c_rv[256];

	Mai_I32 cy_cy;
	Mai_I32 cy_cy2;

	Mai_Bool fColorConvInitOK;


	Mai_Status convertinit();

private:
	Mai_Status blur(Mai_I32* in, Mai_I32* out, Mai_I32 width, Mai_I32 height, Mai_I32_Fixed1 radius);
	Mai_Status blurFractional(Mai_I32* in, Mai_I32* out, Mai_I32 width, Mai_I32 height, Mai_I32_Fixed1 radius);

public:
	Mai_Image(Mai_I32* ptr, Mai_I32 width, Mai_I32 height);
	Mai_Image(Mai_I32 width, Mai_I32 height);
	~Mai_Image();
	Mai_I32* getBitmapPointer();
	Mai_I32 getWidth();
	Mai_I32 getHeight();
	Mai_I32 getType();
	Mai_I32 getPitch();
	Mai_Status fillWith(Mai_I32 color);
	Mai_Status setAlpha(Mai_I32 alpha);
	Mai_Status fad(Mai_I32_Fixed1 hodo);
	Mai_Status BoxBlur(Mai_I32_Fixed1 hRadius, Mai_I32_Fixed1 vRadius, Mai_I32 iterations);
	Mai_Status shiftAlpha();
	Mai_Status shiftRGB();
	Mai_Status shift();
	Mai_I32 getPoint(Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status resize(Mai_I32 width, Mai_I32 height);
	Mai_Status whirl(Mai_I32_Fixed1 x, Mai_I32_Fixed1 y, Mai_I32_Fixed1 angle);
	Mai_Status zwhirl(Mai_I32_Fixed1 angle);
	Mai_Status copyTo(Mai_Image* dst);
	Mai_Status convertTo(Mai_I32 type_dst);
	Mai_Status mixToAVS(SubPicDesc* pTarget, Mai_I32 x, Mai_I32 y);
	Mai_Status saveToPng(WCHAR* dst);
public:
	static Mai_I32 GCC(Mai_I32 color1, Mai_I32 color2, Mai_I32_Fixed hodo);
	static Mai_Status mixEx(Mai_Image* i_dst, Mai_Image* i_src0, Mai_Image* i_src1, Mai_I32 i_x, Mai_I32 i_y);
	static Mai_Status mixExt(Mai_Image* i_dst, Mai_Image* i_src0, Mai_Image* i_src1, Mai_I32_Fixed i_x, Mai_I32_Fixed i_y);
	static Mai_Status mix(Mai_Image* i_dst, Mai_Image* i_src0, Mai_Image* i_src1);
	static Mai_Status mixSEx(Mai_Image* i_dst, Mai_Image* i_src0, Mai_Image* i_src1, Mai_I32 i_x, Mai_I32 i_y);
	static Mai_Status mixS(Mai_Image* i_dst, Mai_Image* i_src0, Mai_Image* i_src1);
	static Mai_I32 mixPoint(Mai_I32 src0, Mai_I32 src1);
	static Mai_Image* loadImage(WCHAR* src);
	static Mai_Image* loadImage2(Mai_I8* data, Mai_I32 data_size);
};

/* Mai_Glyph */
class Mai_Glyph_Bitmap
{
private:
	Heap_Alloc0 heap0;
public:
	Mai_I32 rows;
    Mai_I32 width;
    //Mai_I32 pitch;
    Mai_I8*  buffer;

	Mai_I32 horiBearingX;
	Mai_I32 horiBearingY;
    Mai_I32 horiAdvance;

	Mai_I32 vertBearingX;
    Mai_I32 vertBearingY;
    Mai_I32 vertAdvance;

	Mai_I32 ascender;
	Mai_I32 descender;
    //short           num_grays;
    //char            pixel_mode;
    //char            palette_mode;
    //void*           palette;
public:
	Mai_Glyph_Bitmap(Mai_I32 width, Mai_I32 rows);
	~Mai_Glyph_Bitmap();
};

/* Mai_Font */
class Mai_Font
{
public:
	typedef struct _Spans
	{
		struct Span
		{
		  Mai_I32 x, y, width, coverage;
		}* head;
		Mai_I32 n;
	} Spans;

private:
	Mai_Void* library0;
	Mai_Void* face0;
	struct
	{
		Mai_I8* head;
		Mai_I32 size;
	} font_buffer;
	Heap_Alloc0 heap0;

	Mai_I32 is_ok;

	Mai_I32 ascender;
	Mai_I32 descender;

	Mai_I32_Fixed bold;

	Mai_I32 size;

	Mai_I32_Fixed outline_width;
public:
	Mai_Font(WCHAR* src);
	Mai_Status setSize(Mai_I32 size);
	Mai_Glyph_Bitmap* getGlyphBitmap(Mai_I32 charcode);
	Mai_Status doneMaiGlyphBitmap(Mai_Glyph_Bitmap* mgb);
//	static void RasterCallback(const int y, const int count, const FT_Span * const spans, void * const user);
	Spans* getGlyphSpans(Mai_I32 charcode);
	Spans* getGlyphOutlineSpans(Mai_I32 charcode);
	Mai_Status doneSpans(Spans* spans);
	Mai_I32 getAscender();
	Mai_I32 getDescender();
	Mai_I32_Fixed getCharAdvance(WCHAR c);
	Mai_I32_Fixed getStringAdvance(WCHAR* s);
	Mai_Status setBold(Mai_I32_Fixed bold);
	Mai_Status setOutlineWidth(Mai_I32_Fixed outline_width);
};

/* Mai_Graphics */
class Mai_Graphics
{
private:
	Mai_Image* mi0;
	Mai_Font* mf0;
	Mai_I32 color;
	Mai_I32 ocolor;
public:
	Mai_Graphics(Mai_Image* src);
	Mai_Status setColor(Mai_I32 color);
	Mai_Status setOutlineColor(Mai_I32 color);
	Mai_Status setFont(Mai_Font* font);
	Mai_Status drawCharEx(WCHAR cr, Mai_I32_Fixed x, Mai_I32_Fixed y, Mai_Glyph_Bitmap** mgr);
	Mai_Status drawCharWithOutlineEx(WCHAR cr, Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status drawCharWithSpansEx(Mai_Font::Spans* spans, Mai_I32_Fixed x, Mai_I32_Fixed y, Mai_I32 showcolor);
	Mai_Status drawStringEx(WCHAR* s, Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status drawStringWithOutlineEx(WCHAR* s, Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status drawStringExLT(WCHAR* s, Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status drawStringExLT1(WCHAR* s, Mai_I32 off, Mai_I32 length, Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status drawStringExC(WCHAR* s, Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status drawStringExCC(WCHAR* s, Mai_I32_Fixed x, Mai_I32_Fixed y);
	Mai_Status drawPoint0(Mai_I32_Fixed x, Mai_I32_Fixed y, Mai_I32 color);
	Mai_Status drawPoint1(Mai_I32_Fixed x, Mai_I32_Fixed y, Mai_I32 color);
	Mai_Status drawBigPoint0(Mai_I32_Fixed center_x, Mai_I32_Fixed center_y, Mai_I32_Fixed r, Mai_I32 color1, Mai_I32 color2);
};





/* Mai_Particle_System0 */
/*class Mai_Particle_System0
{
public:
	typedef struct _Particle
	{
		Mai_I32_Fixed1 x, y;
		Mai_I32_Fixed1 vx, vy;
		Mai_I32_Fixed1 angle;
		Mai_I32_Fixed1 w;
		Mai_I32 status;
		Mai_I32 count;
		Mai_I32 count_max0, count_max1, count_max2;
	} Particle;

	struct
	{
		Particle* head;
		Mai_I32 n;
		Mai_I32 num;
	} particles;

	struct
	{
		Mai_I32_Fixed1 x;
		Mai_I32_Fixed1 y;
		Mai_I32_Fixed1 r;
		Mai_I32_Fixed1 vo;
	} emitter;

	struct
	{
		Mai_I32_Fixed1 x, y, x_pre, y_pre, x_next, y_next;
		Mai_I32_Fixed1 angle, angle_pre, angle_next;
		Mai_I32_Fixed1 tuyosa;
		Mai_I32 count;
		Mai_I32 count_max;
	} wind0;

	Mai_I32 add_time_dis;
	Mai_I32 add_time_count;

	Heap_Alloc0 heap0;
public:
	Mai_Status initWind();
	Mai_Status nextWind();
public:
	Mai_Particle_System0(Mai_I32 particle_num);
	Mai_Status init(Mai_I32 particle_num);
	Mai_Status setEmitter(Mai_I32_Fixed1 x, Mai_I32_Fixed1 y);
	Particle* getNewParticle();
	Mai_Status copyParticle(Particle* dst, Particle* src);
	//Mai_Status add();
	//Mai_Status del(Mai_I32 s);
	Mai_Status addParticle();
	Mai_Status delParticle(Mai_I32 s);
	Mai_Status nextFrame();
	Mai_Status draw(Mai_Image* src);
};*/

/* Mai_Particle_System1 */
/*class Mai_Particle_System1
{
public:
	typedef struct _Particle
	{
		Mai_I32_Fixed1 x, y;
		Mai_I32_Fixed1 vx, vy;
		Mai_I32_Fixed1 angle;
		Mai_I32_Fixed1 w;
		Mai_I32 status;
		Mai_I32 count;
		Mai_I32 count_max0, count_max1, count_max2;
	} Particle;

	struct _Frame
	{
		Particle* head;
		Mai_I32 n;
		Mai_I32 num;
	} particles, *frames;

	Mai_I32 frames_n;

	struct
	{
		Mai_I32 line[1000];
		Mai_I32 n;
		Mai_I32 n_now;
	} lines;

	struct
	{
		Mai_I32_Fixed1 x;
		Mai_I32_Fixed1 y;
		Mai_I32_Fixed1 r;
		Mai_I32_Fixed1 vo;
	} emitter;

	struct
	{
		Mai_I32_Fixed1 x, y, x_pre, y_pre, x_next, y_next;
		Mai_I32_Fixed1 angle, angle_pre, angle_next;
		Mai_I32_Fixed1 tuyosa;
		Mai_I32 count;
		Mai_I32 count_max;
	} wind0;

	Mai_I32 add_time_dis;
	Mai_I32 add_time_count;

	Heap_Alloc0 heap0;
public:
	Mai_Status initWind();
	Mai_Status nextWind();
private:
	Mai_Image* seed;
	Mai_I32 frame_total;

	Mai_I32 frame_count;
	Mai_Image* ptc;
	Mai_Image* ptc_temp;
public:
	Mai_Particle_System1(Mai_Image* src, Mai_I32 frame_total);
	~Mai_Particle_System1();
	Mai_Status init(Mai_I32 particle_num);
	Mai_Status setEmitter(Mai_I32_Fixed1 x, Mai_I32_Fixed1 y);
	Particle* getNewParticle();
	Mai_Status copyParticle(Particle* dst, Particle* src);
	//Mai_Status add();
	//Mai_Status del(Mai_I32 s);
	Mai_Status addParticle();
	Mai_Status delParticle(Mai_I32 s);
	Mai_Status nextFrame();
	Mai_Status draw(Mai_Image* src, Mai_I32 frame_num);
	Mai_I32 getTotalFrame();
	Mai_Status setPTC(Mai_Image* ptc);
};*/

/* Mai_Particle_System2 */
/*class Mai_Particle_System2
{
public:
	typedef struct _Particle
	{
		Mai_I32_Fixed1 x, y;
		Mai_I32_Fixed1 vx, vy;
		Mai_I32_Fixed1 angle;
		Mai_I32_Fixed1 w;
		Mai_I32 cate;
		Mai_I32 status;
		Mai_I32 count;
		Mai_I32 count_max0, count_max1, count_max2;
	} Particle;

	struct
	{
		Particle* head;
		Mai_I32 n;
		Mai_I32 num;
	} particles;

	struct
	{
		Mai_I32_Fixed1 x;
		Mai_I32_Fixed1 y;
		Mai_I32_Fixed1 r;
		Mai_I32_Fixed1 vo;
	} emitter;

	struct
	{
		Mai_I32_Fixed1 x, y, x_pre, y_pre, x_next, y_next;
		Mai_I32_Fixed1 angle, angle_pre, angle_next;
		Mai_I32_Fixed1 tuyosa;
		Mai_I32 count;
		Mai_I32 count_max;
	} wind0;

	Mai_I32 add_time_dis;
	Mai_I32 add_time_count;

	Heap_Alloc0 heap0;
private:
	struct
	{
		Mai_Image** ptc;
		Mai_I32 n;
		Mai_I32 n_max;
	} ptcs;
	//Mai_Image* ptc;
	Mai_Image* ptc_temp;
	Mai_Bool is_end;
public:
	Mai_Status initWind();
	Mai_Status nextWind();
public:
	Mai_Particle_System2(Mai_I32 particle_num);
	~Mai_Particle_System2();
	Mai_Status init(Mai_I32 particle_num);
	Mai_Status setEmitter(Mai_I32_Fixed1 x, Mai_I32_Fixed1 y);
	Particle* getNewParticle();
	Mai_Status copyParticle(Particle* dst, Particle* src);
	//Mai_Status add();
	//Mai_Status del(Mai_I32 s);
	Mai_Status addParticle();
	Mai_Status delParticle(Mai_I32 s);
	Mai_Status nextFrame();
	Mai_Status draw(Mai_Image* src);
	Mai_Status addPTC(Mai_Image* ptc);
	Mai_Status setEnd(Mai_Bool is_end);
};*/

/* Mai_Particle_System3 */
/*class Mai_Particle_System3
{
public:
	typedef struct _Particle
	{
		Mai_I32_Fixed1 x, y;
		Mai_I32_Fixed1 vx, vy;
		Mai_I32_Fixed1 angle;
		Mai_I32_Fixed1 w;
		Mai_I32 status;
		Mai_I32 count;
		Mai_I32 count_max0, count_max1, count_max2;
	} Particle;

	struct _Frame
	{
		Particle* head;
		Mai_I32 n;
		Mai_I32 num;
	} particles, *frames;

	Mai_I32 frames_n;

	struct
	{
		Mai_I32 line[1000];
		Mai_I32 n;
		Mai_I32 n_now;
	} lines;

	struct
	{
		Mai_I32_Fixed1 x;
		Mai_I32_Fixed1 y;
		Mai_I32_Fixed1 r;
		Mai_I32_Fixed1 vo;
	} emitter;

	struct
	{
		Mai_I32_Fixed1 x, y, x_pre, y_pre, x_next, y_next;
		Mai_I32_Fixed1 angle, angle_pre, angle_next;
		Mai_I32_Fixed1 tuyosa;
		Mai_I32 count;
		Mai_I32 count_max;
	} wind0;

	Mai_I32 add_time_dis;
	Mai_I32 add_time_count;

	Heap_Alloc0 heap0;
public:
	Mai_Status initWind();
	Mai_Status nextWind();
private:
	Mai_Image* seed;
	Mai_I32 frame_total;

	Mai_I32 frame_count;
	Mai_Image* ptc;
	Mai_Image* ptc_temp;
public:
	Mai_Particle_System3(Mai_Image* src, Mai_I32 frame_total);
	~Mai_Particle_System3();
	Mai_Status init(Mai_I32 particle_num);
	Mai_Status setEmitter(Mai_I32_Fixed1 x, Mai_I32_Fixed1 y);
	Particle* getNewParticle();
	Mai_Status copyParticle(Particle* dst, Particle* src);
	//Mai_Status add();
	//Mai_Status del(Mai_I32 s);
	Mai_Status addParticle();
	Mai_Status delParticle(Mai_I32 s);
	Mai_Status nextFrame();
	Mai_Status draw(Mai_Image* src, Mai_I32 frame_num);
	Mai_I32 getTotalFrame();
	Mai_Status setPTC(Mai_Image* ptc);
};*/