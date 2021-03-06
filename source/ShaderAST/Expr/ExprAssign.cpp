/*
See LICENSE file in root folder
*/
#include "ShaderAST/Expr/ExprAssign.hpp"

#include "ShaderAST/Expr/ExprVisitor.hpp"

namespace ast::expr
{
	Assign::Assign( type::TypePtr type
		, ExprPtr lhs
		, ExprPtr rhs
		, Kind kind )
		: Binary{ std::move( type )
			, std::move( lhs )
			, std::move( rhs )
			, kind }
	{
	}

	void Assign::accept( VisitorPtr vis )
	{
		vis->visitAssignExpr( this );
	}
}
