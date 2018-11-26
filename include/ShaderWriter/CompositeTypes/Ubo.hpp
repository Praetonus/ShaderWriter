/*
See LICENSE file in root folder
*/
#ifndef ___SDW_Ubo_H___
#define ___SDW_Ubo_H___

#include "BoInfo.hpp"

#include <ShaderAST/Stmt/StmtConstantBufferDecl.hpp>

namespace sdw
{
	class Ubo
	{
	public:
		using Info = BoInfo;

		Ubo( ShaderWriter & writer
			, std::string const & name
			, uint32_t bind
			, uint32_t set
			, ast::type::MemoryLayout layout = ast::type::MemoryLayout::eStd140 );
		void end();

		StructInstance declMember( std::string const & name, Struct const & s );
		template< typename T >
		inline T declMember( std::string const & name );
		template< typename T >
		inline Array< T > declMember( std::string const & name
			, uint32_t dimension );
		template< typename T >
		inline Optional< T > declMember( std::string const & name
			, bool enabled );
		template< typename T >
		inline Optional< Array< T > > declMember( std::string const & name
			, uint32_t dimension
			, bool enabled );
		template< typename T >
		inline T getMember( std::string const & name );
		template< typename T >
		inline Array< T > getMemberArray( std::string const & name );
		template< typename T >
		inline Optional< T > getMember( std::string const & name
			, bool enabled );
		template< typename T >
		inline Optional< Array< T > > getMemberArray( std::string const & name
			, bool enabled );

	private:
		Shader & m_shader;
		stmt::ConstantBufferDeclPtr m_stmt;
		std::string m_name;
		Info m_info;
		var::VariablePtr m_var;
	};
}

#include "Ubo.inl"

#endif
