#ifndef WELS_VIDEO_CODEC_DEFINITION_H__
#define WELS_VIDEO_CODEC_DEFINITION_H__

typedef struct TagSysMemBuffer {
  int iWidth;                    ///< width of decoded pic for display
  int iHeight;                   ///< height of decoded pic for display
  int iFormat;                   ///< type is "EVideoFormatType"
  int iStride[2];                ///< stride of 2 component
} SSysMEMBuffer;

typedef struct TagBufferInfo {
  int iBufferStatus;             ///< 0: one frame data is not ready; 1: one frame data is ready
  unsigned long long uiInBsTimeStamp;     ///< input BS timestamp
  unsigned long long uiOutYuvTimeStamp;     ///< output YUV timestamp, when bufferstatus is 1
  union {
    SSysMEMBuffer sSystemBuffer; ///<  memory info for one picture
  } UsrData;                     ///<  output buffer info
  unsigned char* pDst[3];  //point to picture YUV data
} SBufferInfo;

typedef enum {
  videoFormatRGB        = 1,             ///< rgb color formats
  videoFormatRGBA       = 2,
  videoFormatRGB555     = 3,
  videoFormatRGB565     = 4,
  videoFormatBGR        = 5,
  videoFormatBGRA       = 6,
  videoFormatABGR       = 7,
  videoFormatARGB       = 8,

  videoFormatYUY2       = 20,            ///< yuv color formats
  videoFormatYVYU       = 21,
  videoFormatUYVY       = 22,
  videoFormatI420       = 23,            ///< the same as IYUV
  videoFormatYV12       = 24,
  videoFormatInternal   = 25,            ///< only used in SVC decoder testbed

  videoFormatNV12       = 26,            ///< new format for output by DXVA decoding

  videoFormatVFlip      = 0x80000000
} EVideoFormatType;

#endif