#ifndef WELS_VIDEO_CODEC_APPLICATION_DEFINITION_H__
#define WELS_VIDEO_CODEC_APPLICATION_DEFINITION_H__

typedef enum {
  DECODER_OPTION_END_OF_STREAM = 1,     ///< end of stream flag
  DECODER_OPTION_VCL_NAL,               ///< feedback whether or not have VCL NAL in current AU for application layer
  DECODER_OPTION_TEMPORAL_ID,           ///< feedback temporal id for application layer
  DECODER_OPTION_FRAME_NUM,             ///< feedback current decoded frame number
  DECODER_OPTION_IDR_PIC_ID,            ///< feedback current frame belong to which IDR period
  DECODER_OPTION_LTR_MARKING_FLAG,      ///< feedback wether current frame mark a LTR
  DECODER_OPTION_LTR_MARKED_FRAME_NUM,  ///< feedback frame num marked by current Frame
  DECODER_OPTION_ERROR_CON_IDC,         ///< indicate decoder error concealment method
  DECODER_OPTION_TRACE_LEVEL,
  DECODER_OPTION_TRACE_CALLBACK,        ///< a void (*)(void* context, int level, const char* message) function which receives log messages
  DECODER_OPTION_TRACE_CALLBACK_CONTEXT,///< context info of trace callbac

  DECODER_OPTION_GET_STATISTICS,        ///< feedback decoder statistics
  DECODER_OPTION_GET_SAR_INFO,          ///< feedback decoder Sample Aspect Ratio info in Vui
  DECODER_OPTION_PROFILE,               ///< get current AU profile info, only is used in GetOption
  DECODER_OPTION_LEVEL,                 ///< get current AU level info,only is used in GetOption
  DECODER_OPTION_STATISTICS_LOG_INTERVAL,///< set log output interval
  DECODER_OPTION_IS_REF_PIC,             ///< feedback current frame is ref pic or not
  DECODER_OPTION_NUM_OF_FRAMES_REMAINING_IN_BUFFER,  ///< number of frames remaining in decoder buffer when pictures are required to re-ordered into display-order.
  DECODER_OPTION_NUM_OF_THREADS,         ///< number of decoding threads. The maximum thread count is equal or less than lesser of (cpu core counts and 16).
} DECODER_OPTION;

typedef enum {
  /**
  * Errors derived from bitstream parsing
  */
  dsErrorFree = 0x00,   ///< bit stream error-free
  dsFramePending = 0x01,   ///< need more throughput to generate a frame output,
  dsRefLost = 0x02,   ///< layer lost at reference frame with temporal id 0
  dsBitstreamError = 0x04,   ///< error bitstreams(maybe broken internal frame) the decoder cared
  dsDepLayerLost = 0x08,   ///< dependented layer is ever lost
  dsNoParamSets = 0x10,   ///< no parameter set NALs involved
  dsDataErrorConcealed = 0x20,   ///< current data error concealed specified
  dsRefListNullPtrs = 0x40, ///<ref picure list contains null ptrs within uiRefCount range

  /**
  * Errors derived from logic level
  */
  dsInvalidArgument     = 0x1000, ///< invalid argument specified
  dsInitialOptExpected  = 0x2000, ///< initializing operation is expected
  dsOutOfMemory         = 0x4000, ///< out of memory due to new request
  /**
  * ANY OTHERS?
  */
  dsDstBufNeedExpan     = 0x8000  ///< actual picture size exceeds size of dst pBuffer feed in decoder, so need expand its size

} DECODING_STATE;

typedef struct TagParserBsInfo {
  int iNalNum;                                 ///< total NAL number in current AU
  int* pNalLenInByte;  ///< each nal length
  unsigned char* pDstBuff;                     ///< outputted dst buffer for parsed bitstream
  int iSpsWidthInPixel;                        ///< required SPS width info
  int iSpsHeightInPixel;                       ///< required SPS height info
  unsigned long long uiInBsTimeStamp;               ///< input BS timestamp
  unsigned long long uiOutBsTimeStamp;             ///< output BS timestamp
} SParserBsInfo, *PParserBsInfo;

typedef enum {
  ERROR_CON_DISABLE = 0,
  ERROR_CON_FRAME_COPY,
  ERROR_CON_SLICE_COPY,
  ERROR_CON_FRAME_COPY_CROSS_IDR,
  ERROR_CON_SLICE_COPY_CROSS_IDR,
  ERROR_CON_SLICE_COPY_CROSS_IDR_FREEZE_RES_CHANGE,
  ERROR_CON_SLICE_MV_COPY_CROSS_IDR,
  ERROR_CON_SLICE_MV_COPY_CROSS_IDR_FREEZE_RES_CHANGE
} ERROR_CON_IDC;

typedef enum {
  VIDEO_BITSTREAM_AVC               = 0,
  VIDEO_BITSTREAM_SVC               = 1,
  VIDEO_BITSTREAM_DEFAULT           = VIDEO_BITSTREAM_SVC
} VIDEO_BITSTREAM_TYPE;

typedef struct {
  unsigned int          size;          ///< size of the struct
  VIDEO_BITSTREAM_TYPE  eVideoBsType;  ///< video stream type (AVC/SVC)
} SVideoProperty;

typedef struct TagSVCDecodingParam {
  char*     pFileNameRestructed;       ///< file name of reconstructed frame used for PSNR calculation based debug

  unsigned int  uiCpuLoad;             ///< CPU load
  unsigned char uiTargetDqLayer;       ///< setting target dq layer id

  ERROR_CON_IDC eEcActiveIdc;          ///< whether active error concealment feature in decoder
  bool bParseOnly;                     ///< decoder for parse only, no reconstruction. When it is true, SPS/PPS size should not exceed SPS_PPS_BS_SIZE (128). Otherwise, it will return error info

  SVideoProperty   sVideoProperty;    ///< video stream property
} SDecodingParam, *PDecodingParam;

#endif