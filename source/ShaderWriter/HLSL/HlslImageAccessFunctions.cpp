/*
See LICENSE file in root folder
*/
#include "ShaderWriter/HLSL/HlslIntrinsicFunctions.hpp"
#include "ShaderWriter/HLSL/HlslExprAdapter.hpp"

#include <ShaderAST/Stmt/StmtContainer.hpp>
#include <ShaderAST/Stmt/StmtComment.hpp>

namespace sdw::hlsl
{
	namespace details
	{
		using namespace ast;

		inline void writeImageSamples2DMS( stmt::Container * container, std::string const & type )
		{
			auto cont = stmt::makeContainer();
			cont->addStmt( stmt::makeComment( "int SDW_imageSamples(" + type + " image)" ) );
			cont->addStmt( stmt::makeComment( "{" ) );
			cont->addStmt( stmt::makeComment( "	uint dumpX;" ) );
			cont->addStmt( stmt::makeComment( "	uint dumpY;" ) );
			cont->addStmt( stmt::makeComment( "	uint res;" ) );
			cont->addStmt( stmt::makeComment( "	image.GetDimensions(dumpX, dumpY, res);" ) );
			cont->addStmt( stmt::makeComment( "	return int(res);" ) );
			cont->addStmt( stmt::makeComment( "}" ) );
			container->addStmt( std::move( cont ) );
		}

		inline void writeImageSamples2DMSArray( stmt::Container * container, std::string const & type )
		{
			auto cont = stmt::makeContainer();
			cont->addStmt( stmt::makeComment( "int SDW_imageSamples(" + type + " image)" ) );
			cont->addStmt( stmt::makeComment( "{" ) );
			cont->addStmt( stmt::makeComment( "	uint dumpX;" ) );
			cont->addStmt( stmt::makeComment( "	uint dumpY;" ) );
			cont->addStmt( stmt::makeComment( "	uint dumpZ;" ) );
			cont->addStmt( stmt::makeComment( "	uint res;" ) );
			cont->addStmt( stmt::makeComment( "	image.GetDimensions(dumpX, dumpY, dumpZ, res);" ) );
			cont->addStmt( stmt::makeComment( "	return int(res);" ) );
			cont->addStmt( stmt::makeComment( "}" ) );
			container->addStmt( std::move( cont ) );
		}
	}

	void compileHlslImageAccessFunctions( ast::stmt::Container * container
		, IntrinsicsConfig const & config )
	{
		//if ( config.requiresImageSamples2DMSF )
		//{
		//	details::writeImageSamples2DMS( container, "RWTexture2D<float4>" );
		//}
		//if ( config.requiresImageSamples2DMSI )
		//{
		//	details::writeImageSamples2DMS( container, "RWTexture2D<int4>" );
		//}
		//if ( config.requiresImageSamples2DMSU )
		//{
		//	details::writeImageSamples2DMS( container, "RWTexture2D<uint4>" );
		//}
		//if ( config.requiresImageSamples2DMSArrayF )
		//{
		//	details::writeImageSamples2DMSArray( container, "RWTexture2DArray<float4>" );
		//}
		//if ( config.requiresImageSamples2DMSArrayI )
		//{
		//	details::writeImageSamples2DMSArray( container, "RWTexture2DArray<int4>" );
		//}
		//if ( config.requiresImageSamples2DMSArrayU )
		//{
		//	details::writeImageSamples2DMSArray( container, "RWTexture2DArray<uint4>" );
		//}
	}
}
