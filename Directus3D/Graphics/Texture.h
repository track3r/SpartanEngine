/*
Copyright(c) 2016 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES =============================
#include "../Graphics/D3D11/D3D11Shader.h"
//========================================

#define NULL_TEXTURE_ID "-1"
#define TEXTURE_PATH_UNKNOWN "-1"

enum TextureType
{
	Albedo,
	Roughness,
	Metallic,
	Normal,
	Height,
	Occlusion,
	Emission,
	Mask,
	CubeMap,
};

class Texture
{
public:
	Texture();
	~Texture();

	//= IO =========================================================================
private:
	void Serialize() const;
	void Deserialize();
public:
	void SaveToFile(std::string filePath);
	bool LoadFromFile(const std::string& filePath);
	//==============================================================================

	ID3D11ShaderResourceView* GetID3D11ShaderResourceView() const;
	void SetID3D11ShaderResourceView(ID3D11ShaderResourceView* srv);

	bool LoadFromFile(std::string path, TextureType expectedType);

	std::string GetID() const;

	void SetName(std::string name);
	std::string GetName();

	void SetFilePath(std::string filepath);
	std::string GetFilePath();

	void SetWidth(int width);
	int GetWidth() const;

	void SetHeight(int height);
	int GetHeight() const;

	TextureType GetType() const;
	void SetType(TextureType type);

	void SetGrayscale(bool grayscale);
	bool GetGrayscale() const;

	void SetTransparency(bool transparency);
	bool GetTransparency();

private:
	std::string m_ID;
	std::string m_name;
	std::string m_filePath;
	int m_width;
	int m_height;
	TextureType m_type;
	bool m_grayscale;
	bool m_transparency;
	bool m_alphaIsTransparency;
	
	ID3D11ShaderResourceView* m_shaderResourceView;
};
