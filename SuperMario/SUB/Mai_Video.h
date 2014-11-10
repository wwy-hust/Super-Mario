/* MaiMpeg2PSDemuxer */
class MaiMpeg2PSDemuxer
{
private:
	Mai_Quene0 *mqi0;
	BitMachineIn0 *bmi0;
	struct
	{
		Mai_Quene0 *mqo[64];
		Mai_I32 id[64];
		Mai_I32 num;
		Mai_I32 num_max;
	} tracks;

	Mai_I32 pack_size;
public:
	MaiMpeg2PSDemuxer();
	Mai_Quene0* getInputQuene();
	Mai_Quene0* getOutputQuene(Mai_U8 stream_id);
	Mai_Status setPackSize(Mai_I32 pack_size);
	Mai_Status demuxPack();
};
