#include "stdafx.h"
#include "CMeshNode.h"
#include "ISceneManager.h"
#include "gfMath.h"
#include "ILightNode.h"
#include "CShaderVariableInjection.h"

namespace gf
{

	void CMeshNode::render(E_PIPELINE_USAGE usage)
	{
		if (!mMaterial)
			return;

		mMesh->bind();

		IPipeline* pipeline = mMaterial->getPipeline(usage);

		CShaderVariableInjection::inject(this, pipeline, 0);

		pipeline->apply(usage);

		mMesh->draw();
		
	}

	void CMeshNode::OnRegisterSceneNode(bool bRecursion)
	{
		if (mVisible)
		{
			calcSortCode();
			mSceneManager->registerNodeForRendering(this);
			if (bRecursion)
				ISceneNode::OnRegisterSceneNode();
		}
	}

	bool CMeshNode::setMaterialName(const std::string& name, u32 subset)
	{
		IMaterial* material = mSceneManager->getVideoDriver()->getMaterialManager()->get(name);
		if (material == nullptr)
			return false;

		ReleaseReferenceCounted(mMaterial);
		mMaterial = material;
		AddReferenceCounted(mMaterial);
		return true;
	}

	void CMeshNode::calcSortCode()
	{
		/* customed order - 8 bit, mesh - 8 bit, pipeline - 48 bit */

		IVideoDriver* driver = mSceneManager->getVideoDriver();
		E_PIPELINE_USAGE usage = driver->getPipelineUsage();

		u32 meshCode = (mMesh) ? mMesh->getSortCode() : 0;
		u64 pipeCode = (mMaterial && mMaterial->getPipeline(usage)) ? mMaterial->getPipeline(usage)->getSortCode() : 0;

		mSortCode = ((u64)mRenderOrder << 56) | ((u64)meshCode << 48) | pipeCode;
	}
}


