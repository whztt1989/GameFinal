#ifndef __TEXTRUE_1D_INTERFACE_H__
#define __TEXTRUE_1D_INTERFACE_H__

#include "ITexture.h"

class ITexture1D : public ITexture
{
	ITexture1D(const std::string& name, u32 sortcode)
	:ITexture(name, sortcode)
	{

	}

	virtual E_TEXTURE_TYPE getType() const
	{
		return ETT_TEXTURE_3D;
	}

	virtual ~ITexture3D() {}
};


#endif

