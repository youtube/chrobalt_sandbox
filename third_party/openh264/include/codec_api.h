#ifndef WELS_VIDEO_CODEC_SVC_API_H__
#define WELS_VIDEO_CODEC_SVC_API_H__

#include "third_party/openh264/include/codec_app_def.h"
#include "third_party/openh264/include/codec_def.h"

#define EXTAPI

class ISVCDecoder {
 public:

  /**
  * @brief  Initilaize decoder
  * @param  pParam  parameter for decoder
  * @return 0 - success; otherwise - failed;
  */
  virtual long EXTAPI Initialize (const SDecodingParam* pParam) = 0;

  /// Uninitialize the decoder
  virtual long EXTAPI Uninitialize() = 0;

  /**
  * @brief   Decode one frame
  * @param   pSrc the h264 stream to be decoded
  * @param   iSrcLen the length of h264 stream
  * @param   ppDst buffer pointer of decoded data (YUV)
  * @param   pStride output stride
  * @param   iWidth output width
  * @param   iHeight output height
  * @return  0 - success; otherwise -failed;
  */
  virtual DECODING_STATE EXTAPI DecodeFrame (const unsigned char* pSrc,
      const int iSrcLen,
      unsigned char** ppDst,
      int* pStride,
      int& iWidth,
      int& iHeight) = 0;

  /**
    * @brief    For slice level DecodeFrameNoDelay() (4 parameters input),
    *           whatever the function return value is, the output data
    *           of I420 format will only be available when pDstInfo->iBufferStatus == 1,.
    *           This function will parse and reconstruct the input frame immediately if it is complete
    *           It is recommended as the main decoding function for H.264/AVC format input
    * @param   pSrc the h264 stream to be decoded
    * @param   iSrcLen the length of h264 stream
    * @param   ppDst buffer pointer of decoded data (YUV)
    * @param   pDstInfo information provided to API(width, height, etc.)
    * @return  0 - success; otherwise -failed;
    */
  virtual DECODING_STATE EXTAPI DecodeFrameNoDelay (const unsigned char* pSrc,
      const int iSrcLen,
      unsigned char** ppDst,
      SBufferInfo* pDstInfo) = 0;

  /**
  * @brief    For slice level DecodeFrame2() (4 parameters input),
  *           whatever the function return value is, the output data
  *           of I420 format will only be available when pDstInfo->iBufferStatus == 1,.
  *           (e.g., in multi-slice cases, only when the whole picture
  *           is completely reconstructed, this variable would be set equal to 1.)
  * @param   pSrc the h264 stream to be decoded
  * @param   iSrcLen the length of h264 stream
  * @param   ppDst buffer pointer of decoded data (YUV)
  * @param   pDstInfo information provided to API(width, height, etc.)
  * @return  0 - success; otherwise -failed;
  */
  virtual DECODING_STATE EXTAPI DecodeFrame2 (const unsigned char* pSrc,
      const int iSrcLen,
      unsigned char** ppDst,
      SBufferInfo* pDstInfo) = 0;


  /**
  * @brief   This function gets a decoded ready frame remaining in buffers after the last frame has been decoded.
  * Use GetOption with option DECODER_OPTION_NUM_OF_FRAMES_REMAINING_IN_BUFFER to get the number of frames remaining in buffers.
  * Note that it is only applicable for profile_idc != 66
  * @param   ppDst buffer pointer of decoded data (YUV)
  * @param   pDstInfo information provided to API(width, height, etc.)
  * @return  0 - success; otherwise -failed;
  */
  virtual DECODING_STATE EXTAPI FlushFrame (unsigned char** ppDst,
      SBufferInfo* pDstInfo) = 0;

  /**
  * @brief   This function parse input bitstream only, and rewrite possible SVC syntax to AVC syntax
  * @param   pSrc the h264 stream to be decoded
  * @param   iSrcLen the length of h264 stream
  * @param   pDstInfo bit stream info
  * @return  0 - success; otherwise -failed;
  */
  virtual DECODING_STATE EXTAPI DecodeParser (const unsigned char* pSrc,
      const int iSrcLen,
      SParserBsInfo* pDstInfo) = 0;

  /**
  * @brief   This API does not work for now!! This is for future use to support non-I420 color format output.
  * @param   pSrc the h264 stream to be decoded
  * @param   iSrcLen the length of h264 stream
  * @param   pDst buffer pointer of decoded data (YUV)
  * @param   iDstStride output stride
  * @param   iDstLen bit stream info
  * @param   iWidth output width
  * @param   iHeight output height
  * @param   iColorFormat output color format
  * @return  to do ...
  */
  virtual DECODING_STATE EXTAPI DecodeFrameEx (const unsigned char* pSrc,
      const int iSrcLen,
      unsigned char* pDst,
      int iDstStride,
      int& iDstLen,
      int& iWidth,
      int& iHeight,
      int& iColorFormat) = 0;

  /**
  * @brief   Set option for decoder, detail option type, please refer to enumurate DECODER_OPTION.
  * @param   pOption  option for decoder such as OutDataFormat, Eos Flag, EC method, ...
  * @return  CM_RETURN: 0 - success; otherwise - failed;
  */
  virtual long EXTAPI SetOption (DECODER_OPTION eOptionId, void* pOption) = 0;

  /**
  * @brief   Get option for decoder, detail option type, please refer to enumurate DECODER_OPTION.
  * @param   pOption  option for decoder such as OutDataFormat, Eos Flag, EC method, ...
  * @return  CM_RETURN: 0 - success; otherwise - failed;
  */
  virtual long EXTAPI GetOption (DECODER_OPTION eOptionId, void* pOption) = 0;
  virtual ~ISVCDecoder() {}
};

#endif
