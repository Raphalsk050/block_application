#include "block_engine/src/platform/opengl/opengl_texture.h"

#include "block_engine/third_party/stb_image/stb_image.h"

#include "block_engine/bepch.h"

namespace BEngine {

namespace Utils {

static GLenum HazelImageFormatToGLDataFormat(ImageFormat format) {
  switch (format) {
    case ImageFormat::RGB8:
      return GL_RGB;
    case ImageFormat::RGBA8:
      return GL_RGBA;
  }

  BENGINE_CORE_ASSERT(false);
  return 0;
}

static GLenum HazelImageFormatToGLInternalFormat(ImageFormat format) {
  switch (format) {
    case ImageFormat::RGB8:
      return GL_RGB8;
    case ImageFormat::RGBA8:
      return GL_RGBA8;
  }

  BENGINE_CORE_ASSERT(false);
  return 0;
}

}  // namespace Utils

OpenGLTexture2D::OpenGLTexture2D(const TextureSpecification& specification)
    : m_Specification(specification),
      m_Width(m_Specification.Width),
      m_Height(m_Specification.Height) {
  BENGINE_PROFILE_FUNCTION();

  m_InternalFormat =
      Utils::HazelImageFormatToGLInternalFormat(m_Specification.Format);
  m_DataFormat = Utils::HazelImageFormatToGLDataFormat(m_Specification.Format);

  glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
  glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

  glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path) {
  BENGINE_PROFILE_FUNCTION();

  int width, height, channels;
  stbi_set_flip_vertically_on_load(1);
  stbi_uc* data = nullptr;
  {
    BENGINE_PROFILE_SCOPE(
        "stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
    data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  }

  if (data) {
    m_IsLoaded = true;

    m_Width = width;
    m_Height = height;

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4) {
      internalFormat = GL_RGBA8;
      dataFormat = GL_RGBA;
    } else if (channels == 3) {
      internalFormat = GL_RGB8;
      dataFormat = GL_RGB;
    }

    m_InternalFormat = internalFormat;
    m_DataFormat = dataFormat;

    BENGINE_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

    glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat,
                        GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
  }
}

OpenGLTexture2D::~OpenGLTexture2D() {
  BENGINE_PROFILE_FUNCTION();

  glDeleteTextures(1, &m_RendererID);
}

void OpenGLTexture2D::SetData(void* data, uint32_t size) {
  BENGINE_PROFILE_FUNCTION();

  uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
  BENGINE_CORE_ASSERT(size == m_Width * m_Height * bpp,
                 "Data must be entire texture!");
  glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat,
                      GL_UNSIGNED_BYTE, data);
}

void OpenGLTexture2D::Bind(uint32_t slot) const {
  BENGINE_PROFILE_FUNCTION();

  glBindTextureUnit(slot, m_RendererID);
}
}  // namespace Hazel