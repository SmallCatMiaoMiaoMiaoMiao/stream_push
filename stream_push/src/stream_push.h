//// by fanxiushu 2018-06-27 ��ffmpegΪ����������
//// ���� xdisp_virt ��Ŀ,xdisp_virt��Զ��������Ƴ�����ʵ����ҳ��ʽ���ƣ�ԭ������ʽ���ƣ���ת��������֧����Ƶ��
//// �������أ� https://github.com/fanxiushu/xdisp_virt BLOG: https://blog.csdn.net/fanxiushu/article/details/80996391

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define STREAM_PUSH_MAX_URLS    200 //��ͬʱ��·���������ֵ

///////////////////////////////
enum STREAM_TYPE
{
	VIDEO_STREAM = 1,
	AUDIO_STREAM = 2,
};
////
struct stream_frame_packet_t
{
	enum STREAM_TYPE type;   ////
	
	///buffer�����Ѿ�����õ�H264��AACһ֡���ݣ� H264��Annex-B��ʽ�洢�ģ�������00 00 01 ��00 00 00 01��ʼ��ָ����� AAC�ǰ���ADTSͷ�ĸ�ʽ
	unsigned char*   buffer;
	int              length;
	
	////
};

/////
#define STREAM_STATE_RUN_ALL      1 //ͬʱ������Ƶ����Ƶ
#define STREAM_STATE_RUN_VIDEO    2 //������Ƶ
#define STREAM_STATE_RUN_AUDIO    3 //������Ƶ
#define STREAM_STATE_PAUSE        4 //��ͣ
#define STREAM_STATE_STOP         5 //ֹͣ
#define STREAM_STATE_DELETE       6 //ɾ��

/////
#define STREAM_URL_STATE_HEADEZR_SIZE  (sizeof(int)*3)
#pragma pack(1)
struct stream_url_state_t
{
	int            total_size;    ///��������С
	int            stream_state;  ///��Ӧ���� STREAM_STATE_XXX
	unsigned int   unique_id;     ///���>0 �� total_size == STREAM_URL_STATE_HEADEZR_SIZE������� unique_id �жϣ�����ʹ�� url �����ж�
	char           url[0];        /// 
};
#pragma pack()


/// function

void* stream_push_create();
void  stream_push_destroy(void* handle);

int stream_push_post_encoded_frame(void* handle, struct stream_frame_packet_t* frame); //����ʵʱ����ʽͶ���Ѿ�����õ�H264��AAC-LC����֡

int stream_push_modify_url(void* handle, struct stream_url_state_t* u);

int stream_push_query_url(void* handle, int is_network_order,
	      struct stream_url_state_t** p_array, int* p_count, int* p_size);

int stream_push_query_state(void* handle,
	int* p_all, int* p_video, int*p_audio, int*p_pause, int* p_stop);

void stream_push_free_memory(void* ptr);//�ͷ� stream_push_query_url ������ڴ�

////
int stream_push_add_url(void* handle, const char* url);
int stream_push_remove_url(void* handle, const char* url);

/// simple video encoder
int simple_video_encode(unsigned char* rgb32, int rgb32_len,
	int width, int height,
	unsigned char* out, int out_len);


#ifdef __cplusplus
}
#endif


