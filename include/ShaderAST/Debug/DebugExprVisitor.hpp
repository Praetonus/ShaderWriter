/*
See LICENSE file in root folder
*/
#ifndef ___AST_DebugExprVisitor_H___
#define ___AST_DebugExprVisitor_H___
#pragma once

#include "ShaderAST/Expr/ExprVisitor.hpp"

namespace ast::debug
{
	class ExprVisitor
		: public expr::SimpleVisitor
	{
	protected:
		ExprVisitor( std::string & result );

	public:
		static std::string submit( expr::Expr * expr );

	private:
		void wrap( expr::Expr * expr );
		void visitUnaryExpr( expr::Unary * expr )override;
		void visitBinaryExpr( expr::Binary * expr )override;

		void visitAggrInitExpr( expr::AggrInit * expr )override;
		void visitCastExpr( expr::Cast * expr )override;
		void visitCompositeConstructExpr( expr::CompositeConstruct * expr )override;
		void visitMbrSelectExpr( expr::MbrSelect * expr )override;
		void visitFnCallExpr( expr::FnCall * expr )override;
		void visitIntrinsicCallExpr( expr::IntrinsicCall * expr )override;
		void visitTextureAccessCallExpr( expr::TextureAccessCall * expr )override;
		void visitImageAccessCallExpr( expr::ImageAccessCall * expr )override;
		void visitIdentifierExpr( expr::Identifier * expr )override;
		void visitInitExpr( expr::Init * expr )override;
		void visitLiteralExpr( expr::Literal * expr )override;
		void visitQuestionExpr( expr::Question * expr )override;
		void visitSwitchCaseExpr( expr::SwitchCase * expr )override;
		void visitSwitchTestExpr( expr::SwitchTest * expr )override;
		void visitSwizzleExpr( expr::Swizzle * expr )override;

	private:
		std::string & m_result;
	};
};

#endif
