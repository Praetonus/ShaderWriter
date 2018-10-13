#include "ShaderWriter/UInt.hpp"

#include "ShaderWriter/Int.hpp"

#include <ASTGenerator/Expr/ExprAddAssign.hpp>
#include <ASTGenerator/Expr/ExprAndAssign.hpp>
#include <ASTGenerator/Expr/ExprBitAnd.hpp>
#include <ASTGenerator/Expr/ExprBitNot.hpp>
#include <ASTGenerator/Expr/ExprBitOr.hpp>
#include <ASTGenerator/Expr/ExprDivideAssign.hpp>
#include <ASTGenerator/Expr/ExprIdentifier.hpp>
#include <ASTGenerator/Expr/ExprLiteral.hpp>
#include <ASTGenerator/Expr/ExprLShift.hpp>
#include <ASTGenerator/Expr/ExprLShiftAssign.hpp>
#include <ASTGenerator/Expr/ExprMinusAssign.hpp>
#include <ASTGenerator/Expr/ExprModulo.hpp>
#include <ASTGenerator/Expr/ExprModuloAssign.hpp>
#include <ASTGenerator/Expr/ExprOrAssign.hpp>
#include <ASTGenerator/Expr/ExprPostDecrement.hpp>
#include <ASTGenerator/Expr/ExprPostIncrement.hpp>
#include <ASTGenerator/Expr/ExprPreDecrement.hpp>
#include <ASTGenerator/Expr/ExprPreIncrement.hpp>
#include <ASTGenerator/Expr/ExprRShift.hpp>
#include <ASTGenerator/Expr/ExprRShiftAssign.hpp>
#include <ASTGenerator/Expr/ExprTimesAssign.hpp>

namespace sdw
{
	UInt::UInt( stmt::Container * container
		, expr::ExprPtr expr )
		: Value{ container, std::move( expr ) }
	{
	}

	UInt::UInt( UInt && rhs )
		: Value{ std::move( rhs ) }
	{
	}

	UInt::UInt( UInt const & rhs )
		: Value{ rhs }
	{
	}

	UInt::UInt( Value const & rhs )
		: Value{ rhs }
	{
	}

	UInt & UInt::operator=( UInt const & rhs )
	{
		if ( m_container )
		{
			addStmt( *m_container
				, stmt::makeSimple( expr::makeAssign( type::getUInt()
					, makeExpr( m_expr )
					, makeExpr( rhs ) ) ) );
		}
		else
		{
			Value::operator=( rhs );
			m_container = rhs.m_container;
		}

		return *this;
	}

	UInt & UInt::operator=( int32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( uint32_t( rhs ) ) ) ) );
		return *this;
	}

	UInt & UInt::operator=( int64_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( uint64_t( rhs ) ) ) ) );
		return *this;
	}

	UInt & UInt::operator=( uint32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator=( uint64_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt::operator uint32_t()
	{
		return 0u;
	}

	UInt & UInt::operator++()
	{
		m_expr = expr::makePreIncrement( std::move( m_expr ) );
		return *this;
	}

	UInt UInt::operator++( int )
	{
		return UInt{ m_container, expr::makePostIncrement( std::move( m_expr ) ) };
	}

	UInt & UInt::operator--()
	{
		m_expr = expr::makePreDecrement( std::move( m_expr ) );
		return *this;
	}

	UInt UInt::operator--( int )
	{
		return UInt{ m_container, expr::makePostDecrement( std::move( m_expr ) ) };
	}

	UInt & UInt::operator+=( UInt const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAddAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator-=( UInt const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeMinusAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator*=( UInt const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeTimesAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator/=( UInt const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeDivideAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator+=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAddAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator-=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeMinusAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator*=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeTimesAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator/=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeDivideAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator+=( uint32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAddAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator-=( uint32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeMinusAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator*=( uint32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeTimesAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator/=( uint32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeDivideAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator+=( int32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAddAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator-=( int32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeMinusAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator*=( int32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeTimesAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator/=( int32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeDivideAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator%=( int32_t rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeModuloAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt & UInt::operator%=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeModuloAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator<<=( int rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeLShiftAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator>>=( int rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeRShiftAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator<<=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeLShiftAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator>>=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeRShiftAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator&=( int rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAndAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator|=( int rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeOrAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator&=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAndAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator|=( Int const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeOrAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator&=( UInt const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeAndAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	inline UInt & UInt::operator|=( UInt const & rhs )
	{
		addStmt( *m_container
			, stmt::makeSimple( expr::makeOrAssign( type::getUInt()
				, makeExpr( m_expr )
				, makeExpr( rhs ) ) ) );
		return *this;
	}

	UInt operator+( UInt const & lhs, uint32_t rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeAdd( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator-( UInt const & lhs, uint32_t rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeMinus( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator*( UInt const & lhs, uint32_t rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeTimes( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator/( UInt const & lhs, uint32_t rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeDivide( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator+( UInt const & lhs, int32_t rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeAdd( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator-( UInt const & lhs, int32_t rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeMinus( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator*( UInt const & lhs, int32_t rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeTimes( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator/( UInt const & lhs, int32_t rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeDivide( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator+( int32_t lhs, UInt const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeAdd( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator-( int32_t lhs, UInt const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeMinus( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator*( int32_t lhs, UInt const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeTimes( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator/( int32_t lhs, UInt const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeDivide( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator+( uint32_t lhs, UInt const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeAdd( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator-( uint32_t lhs, UInt const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeMinus( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator*( uint32_t lhs, UInt const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeTimes( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator/( uint32_t lhs, UInt const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeDivide( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator%( UInt const & lhs, int rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeModulo( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	UInt operator%( UInt const & lhs, Int const & rhs )
	{
		return UInt{ findContainer( lhs, rhs )
			, expr::makeModulo( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator<<( UInt const & lhs, int rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeLShift( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator>>( UInt const & lhs, int rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeRShift( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator<<( UInt const & lhs, Int const & rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeLShift( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator>>( UInt const & lhs, Int const & rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeRShift( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator<<( UInt const & lhs, UInt const & rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeLShift( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator>>( UInt const & lhs, UInt const & rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeRShift( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator&( UInt const & lhs, int rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeBitAnd( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator|( UInt const & lhs, int rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeBitOr( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator&( UInt const & lhs, Int const & rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeBitAnd( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator|( UInt const & lhs, Int const & rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeBitOr( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator&( UInt const & lhs, UInt const & rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeBitAnd( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator|( UInt const & lhs, UInt const & rhs )
	{
		return Int{ findContainer( lhs, rhs )
			, expr::makeBitOr( type::getUInt()
				, makeExpr( lhs )
				, makeExpr( rhs ) ) };
	}

	inline UInt operator~( UInt const & expr )
	{
		return Int{ expr.m_container
			, expr::makeBitNot( type::getUInt()
				, makeExpr( expr ) ) };
	}
}
