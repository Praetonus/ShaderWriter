#include "../Common.hpp"

#include <ShaderAST/Var/Variable.hpp>
#include <ShaderAST/Debug/DebugExprVisitor.hpp>
#include <ShaderAST/Debug/DebugStmtVisitor.hpp>

namespace
{
	void testPreprocIf( test::TestCounts & testCounts )
	{
		testBegin( "testPreprocIf" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makePreprocIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "ItIsDefined" ) ) );
		testCounts.streams.cout << "PreprocIf:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::ePreprocIf );
		check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eIdentifier );
		check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
		testEnd();
	}
	
	void testPreprocIfDef( test::TestCounts & testCounts )
	{
		testBegin( "testPreprocIfDef" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makePreprocIfDef( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "IsItDefined" ) ) );
		testCounts.streams.cout << "PreprocIfDef:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::ePreprocIfDef );
		check( stmt->getIdentExpr()->getKind() == ast::expr::Kind::eIdentifier );
		check( stmt->getIdentExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
		testEnd();
	}

	void testPreprocElif( test::TestCounts & testCounts )
	{
		testBegin( "testPreprocElif" );
		ast::type::TypesCache cache;
		auto ifStmt = ast::stmt::makePreprocIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "ItIsNotDefined" ) ) );
		auto stmt = ifStmt->createElif( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "ItIsDefined" ) ) );
		testCounts.streams.cout << "PreprocElif:\n" << ast::debug::StmtVisitor::submit( stmt ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::ePreprocElif );
		check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eIdentifier );
		check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
		testEnd();
	}

	void testPreprocElse( test::TestCounts & testCounts )
	{
		testBegin( "testPreprocElse" );
		ast::type::TypesCache cache;
		auto ifStmt = ast::stmt::makePreprocIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "ItIsDefined" ) ) );
		auto stmt = ifStmt->createElse();
		testCounts.streams.cout << "PreprocElse:\n" << ast::debug::StmtVisitor::submit( stmt ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::ePreprocElse );
		testEnd();
	}

	void testPreprocEndif( test::TestCounts & testCounts )
	{
		testBegin( "testPreprocEndif" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makePreprocEndif();
		testCounts.streams.cout << "PreprocEndif:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::ePreprocEndif );
		testEnd();
	}

	void testPreprocDefine( test::TestCounts & testCounts )
	{
		testBegin( "testPreprocDefine" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makePreprocDefine( "DefineIt", ast::expr::makeLiteral( cache, 1 ) );
		testCounts.streams.cout << "PreprocDefine:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::ePreprocDefine );
		check( stmt->getExpr()->getKind() == ast::expr::Kind::eLiteral );
		check( stmt->getExpr()->getType()->getKind() == ast::type::Kind::eInt );
		testEnd();
	}

	void testPreprocExtension( test::TestCounts & testCounts )
	{
		testBegin( "testPreprocExtension" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makePreprocExtension( "GL_arb_coin", ast::stmt::PreprocExtension::ExtStatus::eEnabled );
		testCounts.streams.cout << "PreprocExtension:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::ePreprocExtension );
		check( stmt->getName() == "GL_arb_coin" );
		check( stmt->getStatus() == ast::stmt::PreprocExtension::ExtStatus::eEnabled );
		testEnd();
	}

	void testPreprocVersion( test::TestCounts & testCounts )
	{
		testBegin( "testPreprocVersion" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makePreprocVersion( "430 core" );
		testCounts.streams.cout << "PreprocVersion:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::ePreprocVersion );
		check( stmt->getName() == "430 core" );
		testEnd();
	}

	void testSimpleStatement( test::TestCounts & testCounts )
	{
		testBegin( "testSimpleStatement" );
		ast::type::TypesCache cache;
		auto lhs = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "lhs" ) );
		auto rhs = ast::expr::makeLiteral( cache, 10 );
		auto stmt = ast::stmt::makeSimple( ast::expr::makeInit( std::move( lhs ), std::move( rhs ) ) );
		testCounts.streams.cout << "StmtSimple:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eSimple );
		check( stmt->getExpr()->getKind() == ast::expr::Kind::eInit );
		testEnd();
	}
	
	void testVariableDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testVariableDeclStatement" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeVariableDecl( ast::var::makeVariable( cache.getInt(), "lhs" ) );
		testCounts.streams.cout << "StmtVariableDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eVariableDecl );
		check( stmt->getVariable()->getType()->getKind() == ast::type::Kind::eInt );
		check( stmt->getVariable()->getName() == "lhs" );
		testEnd();
	}

	void testSampledImageDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testSampledImageDeclStatement" );
		ast::type::TypesCache cache;
		ast::type::ImageConfiguration config{};
		auto stmt = ast::stmt::makeSampledImageDecl( ast::var::makeVariable( cache.getSampledImage( config ), "lhs" ), 1u, 2u );
		testCounts.streams.cout << "StmtSamplerDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eSampledImageDecl );
		check( stmt->getBindingPoint() == 1u );
		check( stmt->getDescriptorSet() == 2u );
		check( stmt->getVariable()->getType()->getKind() == ast::type::Kind::eSampledImage );
		check( stmt->getVariable()->getName() == "lhs" );
		testEnd();
	}

	void testSamplerDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testSamplerDeclStatement" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeSamplerDecl( ast::var::makeVariable( cache.getSampler(), "lhs" ), 1u, 2u );
		testCounts.streams.cout << "StmtSamplerDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eSamplerDecl );
		check( stmt->getBindingPoint() == 1u );
		check( stmt->getDescriptorSet() == 2u );
		check( stmt->getVariable()->getType()->getKind() == ast::type::Kind::eSampler );
		check( stmt->getVariable()->getName() == "lhs" );
		testEnd();
	}

	void testImageDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testImageDeclStatement" );
		ast::type::TypesCache cache;
		ast::type::ImageConfiguration config{};
		auto stmt = ast::stmt::makeImageDecl( ast::var::makeVariable( cache.getImage( config ), "lhs" ), 1u, 2u );
		testCounts.streams.cout << "StmtImageDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eImageDecl );
		check( stmt->getBindingPoint() == 1u );
		check( stmt->getDescriptorSet() == 2u );
		check( stmt->getVariable()->getType()->getKind() == ast::type::Kind::eImage );
		check( stmt->getVariable()->getName() == "lhs" );
		testEnd();
	}

	void testConstantBufferDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testConstantBufferDeclStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeConstantBufferDecl( "Buffer", ast::type::MemoryLayout::eStd140, 1u, 2u );
			testCounts.streams.cout << "StmtConstantBufferDecl (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eConstantBufferDecl );
			check( stmt->getBindingPoint() == 1u );
			check( stmt->getDescriptorSet() == 2u );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeConstantBufferDecl( "Buffer", ast::type::MemoryLayout::eStd140, 1u, 2u );
			stmt->add( ast::stmt::makeVariableDecl( ast::var::makeVariable( cache.getInt(), "i" ) ) );
			stmt->add( ast::stmt::makeVariableDecl( ast::var::makeVariable( cache.getInt(), "j" ) ) );
			testCounts.streams.cout << "StmtConstantBufferDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eConstantBufferDecl );
			check( stmt->getBindingPoint() == 1u );
			check( stmt->getDescriptorSet() == 2u );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testShaderBufferDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testShaderBufferDeclStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeShaderBufferDecl( cache, "Buffer", ast::type::MemoryLayout::eStd430, 1u, 2u );
			testCounts.streams.cout << "StmtShaderBufferDecl (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eShaderBufferDecl );
			check( stmt->getBindingPoint() == 1u );
			check( stmt->getDescriptorSet() == 2u );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeShaderBufferDecl( cache, "Buffer", ast::type::MemoryLayout::eStd430, 1u, 2u );
			stmt->add( ast::stmt::makeVariableDecl( ast::var::makeVariable( cache.getInt(), "i" ) ) );
			stmt->add( ast::stmt::makeVariableDecl( ast::var::makeVariable( cache.getInt(), "j" ) ) );
			testCounts.streams.cout << "StmtShaderBufferDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eShaderBufferDecl );
			check( stmt->getBindingPoint() == 1u );
			check( stmt->getDescriptorSet() == 2u );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testShaderStructBufferDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testShaderStructBufferDeclStatement" );
		{
			ast::type::TypesCache cache;
			auto baseType = cache.getStruct( ast::type::MemoryLayout::eStd430, "BaseType" );
			auto array = cache.getArray( baseType );
			auto type = cache.getStruct( ast::type::MemoryLayout::eStd430, "BufferType" );
			type->declMember( "Data", array );
			auto data = ast::var::makeVariable( type->getMember( "Data" ).type, "Data", ast::var::Flag::eUniform );
			auto instance = ast::var::makeVariable( type, "Inst", ast::var::Flag::eUniform );
			auto stmt = ast::stmt::makeShaderStructBufferDecl( "Buffer", instance, data, 1u, 2u );
			testCounts.streams.cout << "StmtShaderStructBufferDecl (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eShaderStructBufferDecl );
			check( stmt->getBindingPoint() == 1u );
			check( stmt->getDescriptorSet() == 2u );
		}
		{
			ast::type::TypesCache cache;
			auto baseType = cache.getStruct( ast::type::MemoryLayout::eStd430, "BaseType" );
			baseType->declMember( "i", cache.getInt() );
			baseType->declMember( "j", cache.getInt() );
			auto array = cache.getArray( baseType );
			auto type = cache.getStruct( ast::type::MemoryLayout::eStd430, "BufferType" );
			type->declMember( "Data", array );
			auto data = ast::var::makeVariable( type->getMember( "Data" ).type, "Data", ast::var::Flag::eUniform );
			auto instance = ast::var::makeVariable( type, "Inst", ast::var::Flag::eUniform );
			auto stmt = ast::stmt::makeShaderStructBufferDecl( "Buffer", instance, data, 1u, 2u );
			testCounts.streams.cout << "StmtShaderStructBufferDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eShaderStructBufferDecl );
			check( stmt->getBindingPoint() == 1u );
			check( stmt->getDescriptorSet() == 2u );
		}
		testEnd();
	}

	void testInOutVariableDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testInOutVariableDeclStatement" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeInOutVariableDecl( ast::var::makeVariable( cache.getInt(), "lhs", ast::var::Flag::eShaderInput ), 1u );
		testCounts.streams.cout << "StmtInOutVariableDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eInOutVariableDecl );
		check( stmt->getLocation() == 1u );
		check( stmt->getVariable()->getType()->getKind() == ast::type::Kind::eInt );
		check( stmt->getVariable()->getName() == "lhs" );
		testEnd();
	}

	void testInOutStreamVariableDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testInOutStreamVariableDeclStatement" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeInOutStreamVariableDecl( ast::var::makeVariable( cache.getInt(), "lhs", ast::var::Flag::eShaderInput | ast::var::Flag::eGeometryStream )
			, 1u
			, 2u );
		testCounts.streams.cout << "makeInOutStreamVariableDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eInOutVariableDecl );
		check( stmt->getLocation() == 1u );
		check( stmt->getVariable()->getType()->getKind() == ast::type::Kind::eInt );
		check( stmt->getVariable()->getName() == "lhs" );
		check( stmt->getVariable()->isGeometryStream() );
		check( stmt->getStreamIndex() == 2u );
		testEnd();
	}

	void testInOutBlendVariableDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testInOutBlendVariableDeclStatement" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeInOutBlendVariableDecl( ast::var::makeVariable( cache.getInt(), "lhs", ast::var::Flag::eShaderInput | ast::var::Flag::eBlendIndex )
			, 1u
			, 2u );
		testCounts.streams.cout << "StmtInOutBlendVariableDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eInOutVariableDecl );
		check( stmt->getLocation() == 1u );
		check( stmt->getVariable()->getType()->getKind() == ast::type::Kind::eInt );
		check( stmt->getVariable()->getName() == "lhs" );
		check( stmt->getVariable()->isBlendIndex() );
		check( stmt->getBlendIndex() == 2u );
		testEnd();
	}

	void testContainerStatement( test::TestCounts & testCounts )
	{
		testBegin( "testContainerStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeContainer();
			testCounts.streams.cout << "StmtContainer (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eContainer );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "i" ) );
			auto j = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "j" ) );
			auto stmt = ast::stmt::makeContainer();
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			testCounts.streams.cout << "StmtContainer:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eContainer );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testCompoundStatement( test::TestCounts & testCounts )
	{
		testBegin( "testCompoundStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeCompound();
			testCounts.streams.cout << "StmtCompound (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eCompound );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "i" ) );
			auto j = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "j" ) );
			auto stmt = ast::stmt::makeCompound();
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			testCounts.streams.cout << "StmtCompound:" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eCompound );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testIfStatement( test::TestCounts & testCounts )
	{
		testBegin( "testIfStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			testCounts.streams.cout << "StmtIf (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eIf );
			check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eIdentifier );
			check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "i" ) );
			auto j = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "j" ) );
			auto stmt = ast::stmt::makeIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			testCounts.streams.cout << "StmtIf:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eIf );
			check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eIdentifier );
			check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testElseStatement( test::TestCounts & testCounts )
	{
		testBegin( "testElseStatement" );
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto j = ast::var::makeVariable( cache.getInt(), "j" );
			auto stmt = ast::stmt::makeIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			auto elseStmt = stmt->createElse();
			testCounts.streams.cout << "StmtElse (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( elseStmt->getKind() == ast::stmt::Kind::eElse );
			check( elseStmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto j = ast::var::makeVariable( cache.getInt(), "j" );
			auto stmt = ast::stmt::makeIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			auto elseStmt = stmt->createElse();
			elseStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, i ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			elseStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			testCounts.streams.cout << "StmtElse:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( elseStmt->getKind() == ast::stmt::Kind::eElse );
			check( elseStmt->size() == 2u );
		}
		testEnd();
	}

	void testElseIfStatement( test::TestCounts & testCounts )
	{
		testBegin( "testElseIfStatement" );
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto j = ast::var::makeVariable( cache.getInt(), "j" );
			auto stmt = ast::stmt::makeIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			auto elseIfStmt = stmt->createElseIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "l" ) ) );
			testCounts.streams.cout << "StmtElseIf (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( elseIfStmt->getKind() == ast::stmt::Kind::eElseIf );
			check( elseIfStmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto j = ast::var::makeVariable( cache.getInt(), "j" );
			auto stmt = ast::stmt::makeIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			auto elseIfStmt = stmt->createElseIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "l" ) ) );
			elseIfStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, i ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			elseIfStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			testCounts.streams.cout << "StmtElseIf:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( elseIfStmt->getKind() == ast::stmt::Kind::eElseIf );
			check( elseIfStmt->size() == 2u );
		}
		testEnd();
	}

	void testElseIfElseStatement( test::TestCounts & testCounts )
	{
		testBegin( "testElseIfStatement" );
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto j = ast::var::makeVariable( cache.getInt(), "j" );
			auto stmt = ast::stmt::makeIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			stmt->createElseIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "l" ) ) );
			stmt->createElse();
			testCounts.streams.cout << "StmtElse (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto j = ast::var::makeVariable( cache.getInt(), "j" );
			auto stmt = ast::stmt::makeIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			auto elseIfStmt = stmt->createElseIf( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "l" ) ) );
			elseIfStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, i ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			elseIfStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			auto elseStmt = stmt->createElse();
			elseStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, i ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			elseStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			testCounts.streams.cout << "StmtElse:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;
		}
		testEnd();
	}

	void testWhileStatement( test::TestCounts & testCounts )
	{
		testBegin( "testWhileStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeWhile( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			testCounts.streams.cout << "StmtWhile (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eWhile );
			check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eIdentifier );
			check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "i" ) );
			auto j = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "j" ) );
			auto stmt = ast::stmt::makeWhile( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			testCounts.streams.cout << "StmtWhile:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eWhile );
			check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eIdentifier );
			check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testDoWhileStatement( test::TestCounts & testCounts )
	{
		testBegin( "testDoWhileStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeDoWhile( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			testCounts.streams.cout << "StmtDoWhile (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eDoWhile );
			check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eIdentifier );
			check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "i" ) );
			auto j = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "j" ) );
			auto stmt = ast::stmt::makeDoWhile( ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getBool(), "k" ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			testCounts.streams.cout << "StmtDoWhile:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eDoWhile );
			check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eIdentifier );
			check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testForStatement( test::TestCounts & testCounts )
	{
		testBegin( "testForStatement" );
		{
			ast::type::TypesCache cache;
			auto k = ast::var::makeVariable( cache.getInt(), "k" );
			auto stmt = ast::stmt::makeFor( ast::expr::makeInit( ast::expr::makeIdentifier( cache, k ), ast::expr::makeLiteral( cache, 0 ) )
				, ast::expr::makeLessEqual( cache, ast::expr::makeIdentifier( cache, k ), ast::expr::makeLiteral( cache, 10 ) )
				, ast::expr::makePreIncrement( ast::expr::makeIdentifier( cache, k ) ) );
			testCounts.streams.cout << "StmtFor (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eFor );
			check( stmt->getInitExpr()->getKind() == ast::expr::Kind::eInit );
			check( stmt->getInitExpr()->getType()->getKind() == ast::type::Kind::eInt );
			check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eLessEqual );
			check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
			check( stmt->getIncrExpr()->getKind() == ast::expr::Kind::ePreIncrement );
			check( stmt->getIncrExpr()->getType()->getKind() == ast::type::Kind::eInt );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "i" ) );
			auto j = ast::expr::makeIdentifier( cache, ast::var::makeVariable( cache.getInt(), "j" ) );
			auto k = ast::var::makeVariable( cache.getInt(), "k" );
			auto stmt = ast::stmt::makeFor( ast::expr::makeInit( ast::expr::makeIdentifier( cache, k ), ast::expr::makeLiteral( cache, 0 ) )
				, ast::expr::makeLessEqual( cache, ast::expr::makeIdentifier( cache, k ), ast::expr::makeLiteral( cache, 10 ) )
				, ast::expr::makePreIncrement( ast::expr::makeIdentifier( cache, k ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( i ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			stmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( std::move( j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			testCounts.streams.cout << "StmtFor:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eFor );
			check( stmt->getInitExpr()->getKind() == ast::expr::Kind::eInit );
			check( stmt->getInitExpr()->getType()->getKind() == ast::type::Kind::eInt );
			check( stmt->getCtrlExpr()->getKind() == ast::expr::Kind::eLessEqual );
			check( stmt->getCtrlExpr()->getType()->getKind() == ast::type::Kind::eBoolean );
			check( stmt->getIncrExpr()->getKind() == ast::expr::Kind::ePreIncrement );
			check( stmt->getIncrExpr()->getType()->getKind() == ast::type::Kind::eInt );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testStructureDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testStructureDeclStatement" );
		{
			ast::type::TypesCache cache;
			auto type = cache.getStruct( ast::type::MemoryLayout::eStd140, "MyStruct" );
			auto stmt = ast::stmt::makeStructureDecl( type );
			testCounts.streams.cout << "StmtStructureDecl (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eStructureDecl );
			check( stmt->getType()->getName() == "MyStruct" );
			check( stmt->getType()->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto type = cache.getStruct( ast::type::MemoryLayout::eStd140, "MyStruct" );
			type->declMember( "i", cache.getInt() );
			type->declMember( "j", cache.getInt() );
			auto stmt = ast::stmt::makeStructureDecl( type );
			testCounts.streams.cout << "StmtStructureDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eStructureDecl );
			check( stmt->getType()->getName() == "MyStruct" );
			check( stmt->getType()->size() == 2u );
		}
		testEnd();
	}

	void testSwitchStatement( test::TestCounts & testCounts )
	{
		testBegin( "testSwitchStatement" );
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto stmt = ast::stmt::makeSwitch( ast::expr::makeSwitchTest( ast::expr::makeIdentifier( cache, i ) ) );
			testCounts.streams.cout << "StmtSwitch (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eSwitch );
			check( stmt->getTestExpr()->getKind() == ast::expr::Kind::eSwitchTest );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto stmt = ast::stmt::makeSwitch( ast::expr::makeSwitchTest( ast::expr::makeIdentifier( cache, i ) ) );
			stmt->createCase( ast::expr::makeSwitchCase( ast::expr::makeLiteral( cache, 10 ) ) );
			stmt->createDefault();
			testCounts.streams.cout << "StmtSwitch (empty cases):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eSwitch );
			check( stmt->getTestExpr()->getKind() == ast::expr::Kind::eSwitchTest );
			check( stmt->size() == 2u );
		}
		{
			ast::type::TypesCache cache;
			auto i = ast::var::makeVariable( cache.getInt(), "i" );
			auto j = ast::var::makeVariable( cache.getInt(), "j" );
			auto k = ast::var::makeVariable( cache.getInt(), "k" );
			auto stmt = ast::stmt::makeSwitch( ast::expr::makeSwitchTest( ast::expr::makeIdentifier( cache, i ) ) );
			auto caseStmt = stmt->createCase( ast::expr::makeSwitchCase( ast::expr::makeLiteral( cache, 10 ) ) );
			caseStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			caseStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, k ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			auto defaultStmt = stmt->createDefault();
			defaultStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, k ), ast::expr::makeLiteral( cache, 10 ) ) ) );
			defaultStmt->addStmt( ast::stmt::makeSimple( ast::expr::makeInit( ast::expr::makeIdentifier( cache, j ), ast::expr::makeLiteral( cache, 20 ) ) ) );
			testCounts.streams.cout << "StmtSwitch:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eSwitch );
			check( stmt->getTestExpr()->getKind() == ast::expr::Kind::eSwitchTest );
			check( stmt->size() == 2u );
		}
		testEnd();
	}

	void testReturnStatement( test::TestCounts & testCounts )
	{
		testBegin( "testReturnStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeReturn();
			testCounts.streams.cout << "StmtReturn:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eReturn );
		}
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeReturn( ast::expr::makeLiteral( cache, 10 ) );
			testCounts.streams.cout << "StmtReturn:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eReturn );
			check( stmt->getExpr()->getKind() == ast::expr::Kind::eLiteral );
		}
		testEnd();
	}

	void testDiscardStatement( test::TestCounts & testCounts )
	{
		testBegin( "testDiscardStatement" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeDiscard();
		testCounts.streams.cout << "StmtDiscard:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eDiscard );
		testEnd();
	}

	void testInputComputeLayout( test::TestCounts & testCounts )
	{
		testBegin( "testInputComputeLayout" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeInputComputeLayout( 16, 32, 64 );
		testCounts.streams.cout << "StmtInputComputeLayout:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eInputComputeLayout );
		check( stmt->getWorkGroupsX() == 16u );
		check( stmt->getWorkGroupsY() == 32u );
		check( stmt->getWorkGroupsZ() == 64u );
		testEnd();
	}

	void testInputGeometryLayout( test::TestCounts & testCounts )
	{
		testBegin( "testInputGeometryLayout" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeInputGeometryLayout( ast::stmt::InputLayout::eLineStripWithAdjacency );
		testCounts.streams.cout << "StmtInputGeometryLayout:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eInputGeometryLayout );
		check( stmt->getLayout() == ast::stmt::InputLayout::eLineStripWithAdjacency );
		testEnd();
	}

	void testOutputGeometryLayout( test::TestCounts & testCounts )
	{
		testBegin( "testOutputGeometryLayout" );
		ast::type::TypesCache cache;
		auto stmt = ast::stmt::makeOutputGeometryLayout( ast::stmt::OutputLayout::eTriangleStrip, 15u );
		testCounts.streams.cout << "StmtOutputGeometryLayout:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eOutputGeometryLayout );
		check( stmt->getLayout() == ast::stmt::OutputLayout::eTriangleStrip );
		check( stmt->getPrimCount() == 15u );
		testEnd();
	}

	void testFunctionDeclStatement( test::TestCounts & testCounts )
	{
		testBegin( "testFunctionDeclStatement" );
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeFunctionDecl( cache.getFunction( cache.getInt(), {} ), "foo" );
			testCounts.streams.cout << "StmtFunctionDecl (empty):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eFunctionDecl );
			check( stmt->getName() == "foo" );
			check( stmt->getType()->empty() );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeFunctionDecl( cache.getFunction( cache.getInt(), { ast::var::makeVariable( cache.getInt(), "i" ) } ), "foo" );
			testCounts.streams.cout << "StmtFunctionDecl (empty body):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eFunctionDecl );
			check( stmt->getName() == "foo" );
			check( stmt->getType()->size() == 1u );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeFunctionDecl( cache.getFunction( cache.getInt(), { ast::var::makeVariable( cache.getInt(), "i" ), ast::var::makeVariable( cache.getInt(), "j" ) } ), "foo" );
			testCounts.streams.cout << "StmtFunctionDecl (empty body):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eFunctionDecl );
			check( stmt->getName() == "foo" );
			check( stmt->getType()->size() == 2u );
			check( stmt->empty() );
		}
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeFunctionDecl( cache.getFunction( cache.getInt(), {} ), "foo" );
			stmt->addStmt( ast::stmt::makeReturn( ast::expr::makeLiteral( cache, 10 ) ) );
			testCounts.streams.cout << "StmtFunctionDecl (empty parameters list):\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eFunctionDecl );
			check( stmt->getName() == "foo" );
			check( stmt->getType()->empty() );
			check( stmt->size() == 1u );
		}
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeFunctionDecl( cache.getFunction( cache.getInt(), { ast::var::makeVariable( cache.getInt(), "i" ) } ), "foo" );
			stmt->addStmt( ast::stmt::makeReturn(
				ast::expr::makeAdd( cache.getInt(),
					ast::expr::makeIdentifier( cache, *( stmt->getType()->begin() + 0u ) ),
					ast::expr::makeLiteral( cache, 10 ) ) ) );
			testCounts.streams.cout << "StmtFunctionDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eFunctionDecl );
			check( stmt->getName() == "foo" );
			check( stmt->getType()->size() == 1u );
			check( stmt->size() == 1u );
		}
		{
			ast::type::TypesCache cache;
			auto stmt = ast::stmt::makeFunctionDecl( cache.getFunction( cache.getInt(), { ast::var::makeVariable( cache.getInt(), "i" ), ast::var::makeVariable( cache.getInt(), "j" ) } ), "foo" );
			stmt->addStmt( ast::stmt::makeReturn( 
				ast::expr::makeAdd( cache.getInt(), 
					ast::expr::makeIdentifier( cache, *( stmt->getType()->begin() + 0u ) ),
					ast::expr::makeIdentifier( cache, *( stmt->getType()->begin() + 1u ) ) ) ) );
			testCounts.streams.cout << "StmtFunctionDecl:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

			require( stmt->getKind() == ast::stmt::Kind::eFunctionDecl );
			check( stmt->getName() == "foo" );
			check( stmt->getType()->size() == 2u );
			check( stmt->size() == 1u );
		}
		testEnd();
	}

	void testFragmentLayoutStatement( test::TestCounts & testCounts )
	{
		testBegin( "testFragmentLayoutStatement" );
		auto stmt = ast::stmt::makeFragmentLayout( ast::FragmentOrigin::eLowerLeft
			, ast::FragmentCenter::eCenterInteger );
		testCounts.streams.cout << "StmtFragmentLayout:\n" << ast::debug::StmtVisitor::submit( stmt.get() ) << std::endl;

		require( stmt->getKind() == ast::stmt::Kind::eFragmentLayout );
		check( stmt->getFragmentCenter() == ast::FragmentCenter::eCenterInteger );
		check( stmt->getFragmentOrigin() == ast::FragmentOrigin::eLowerLeft );
		testEnd();
	}
}

testSuiteMain( TestASTStatements )
{
	testSuiteBegin();
	testPreprocIf( testCounts );
	testPreprocIfDef( testCounts );
	testPreprocElif( testCounts );
	testPreprocElse( testCounts );
	testPreprocEndif( testCounts );
	testPreprocDefine( testCounts );
	testPreprocExtension( testCounts );
	testPreprocVersion( testCounts );
	testSimpleStatement( testCounts );
	testVariableDeclStatement( testCounts );
	testSampledImageDeclStatement( testCounts );
	testSamplerDeclStatement( testCounts );
	testImageDeclStatement( testCounts );
	testConstantBufferDeclStatement( testCounts );
	testShaderBufferDeclStatement( testCounts );
	testShaderStructBufferDeclStatement( testCounts );
	testInOutVariableDeclStatement( testCounts );
	testInOutStreamVariableDeclStatement( testCounts );
	testInOutBlendVariableDeclStatement( testCounts );
	testContainerStatement( testCounts );
	testCompoundStatement( testCounts );
	testIfStatement( testCounts );
	testElseStatement( testCounts );
	testElseIfStatement( testCounts );
	testElseIfElseStatement( testCounts );
	testWhileStatement( testCounts );
	testDoWhileStatement( testCounts );
	testForStatement( testCounts );
	testStructureDeclStatement( testCounts );
	testSwitchStatement( testCounts );
	testReturnStatement( testCounts );
	testDiscardStatement( testCounts );
	testInputComputeLayout( testCounts );
	testInputGeometryLayout( testCounts );
	testOutputGeometryLayout( testCounts );
	testFunctionDeclStatement( testCounts );
	testFragmentLayoutStatement( testCounts );
	testSuiteEnd();
}

testSuiteLaunch( TestASTStatements )
