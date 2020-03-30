//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Josef Kotoun <xkotou06@stud.fit.vutbr.cz>
// $Date:       $2020-02-16
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Josef Kotoun
 * 
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

class MatrixCreateTest : public ::testing::Test
{
    protected:
    Matrix matrix;
};
class MatrixGetSetTest: public ::testing::Test
{
    protected:
    Matrix matrix_4x4 = Matrix(4,4);
    Matrix matrix_3x1 = Matrix(3,1);
    Matrix matrix_1x3 = Matrix(1,3);
    Matrix matrix_1x1 = Matrix();
};
class MatrixOperationsTest: public MatrixGetSetTest
{
    protected:
    Matrix matrix_1x3_copy = Matrix(1,3);
    Matrix determinant_zero = Matrix(2,2);
    Matrix matrix_2x2 = Matrix(2,2);
    Matrix matrix_3x3 = Matrix(3,3);
    virtual void SetUp()
    {
        matrix_4x4.set(std::vector<std::vector<double>>
        {
            {2,1,2,2},
            {2,2,2,1},
            {1,2,2,2},
            {2,1,2,1}
        });
        matrix_1x1.set(std::vector<std::vector<double>>
        {
            {4}
        });
        //1 radek 3 sloupce
        matrix_1x3.set(std::vector<std::vector<double>>
        {
           {1,3,6}
        });
        matrix_1x3_copy.set(std::vector<std::vector<double>>
        {
           {1,3,6}
        });
        matrix_3x1.set(std::vector<std::vector<double>>
        {
            {1},
            {7},
            {12}
        });
        determinant_zero.set(std::vector<std::vector<double>>
        {
            {1, 3},
            {1, 3}
        });
        matrix_2x2.set(std::vector<std::vector<double>>
        {
            {3, 4},
            {1, 2}
        });
        matrix_3x3.set(std::vector<std::vector<double>>
        {
            {4, 5, 2},
            {3, 4, 1},
            {1, 3, 2}
        });
    }

};

TEST_F(MatrixCreateTest, MatrixCreate)
{
    //spravne vytvoreni
    EXPECT_NO_THROW(Matrix());
    EXPECT_NO_THROW(Matrix(3,3));
    EXPECT_NO_THROW(Matrix(1,1));
    EXPECT_NO_THROW(Matrix(50,42));

    //spatne vytvoreni - index <1
    EXPECT_ANY_THROW(Matrix(0,1));
    EXPECT_ANY_THROW(Matrix(1,0));
    EXPECT_ANY_THROW(Matrix(-1,0));
    
}
TEST_F(MatrixGetSetTest,GetSetSingleValue)
{
    //platne indexy
    EXPECT_TRUE(matrix_1x1.set(0,0,20.5));
    EXPECT_TRUE(matrix_4x4.set(3,2,15.5));
    EXPECT_TRUE(matrix_1x3.set(0,2,2.0));
    EXPECT_TRUE(matrix_3x1.set(1,0,10.2));

    //vybrani hodnoty
    EXPECT_EQ(matrix_1x1.get(0,0),20.5);
    EXPECT_EQ(matrix_4x4.get(3,2), 15.5);
    EXPECT_EQ(matrix_1x3.get(0,2),2.0);
    EXPECT_EQ(matrix_3x1.get(1,0),10.2);
    
    //neplatny index nastaveni
    EXPECT_FALSE(matrix_1x1.set(1,0,15.0));
    EXPECT_FALSE(matrix_4x4.set(4,2,25));
    EXPECT_FALSE(matrix_3x1.set(5,4,15.0));

    //neplay index vybrani
    EXPECT_ANY_THROW(matrix_1x1.get(0,2));
    EXPECT_ANY_THROW(matrix_4x4.get(5,3));
    EXPECT_ANY_THROW(matrix_3x1.get(5,4));
}

TEST_F(MatrixGetSetTest, SetVector)
{
    //spravne zadani hodnot vektorem
    EXPECT_TRUE(matrix_1x1.set(std::vector<std::vector<double>>({{4}})));
    EXPECT_TRUE(matrix_4x4.set(std::vector<std::vector<double>>{        
        {1,2,3,4},
        {4,5,2,3},
        {3,5,23.2,5.3},
        {2,4,5.6,3}
    }));
    EXPECT_TRUE(matrix_1x3.set(std::vector<std::vector<double>>({
        {1,4,5}
    })));

    //vice sloupcu
    EXPECT_FALSE(matrix_3x1.set(std::vector<std::vector<double>>({
        {1,3,2,4}
    })));
    //vice radku
    EXPECT_FALSE(matrix_1x3.set(std::vector<std::vector<double>>({
        {1,2,3},
        {2,4,3}
    })));
    //mene sloupcu
    EXPECT_FALSE(matrix_4x4.set(std::vector<std::vector<double>>({
        {1,3},
        {1,5,4},
        {1,4,3,2},
        {5,4,6,24}
    })));
    //mene radku
    EXPECT_FALSE(matrix_4x4.set(std::vector<std::vector<double>>({
        {1,3},
        {1,5,4},
    })));
}

TEST_F(MatrixOperationsTest, MatrixComparison)
{
    //ruzna velikost
    EXPECT_ANY_THROW(matrix_4x4 == matrix_3x1);
    EXPECT_ANY_THROW(matrix_1x1 == matrix_3x1);
    //stejna velikost, ruzne hodnoty
    Matrix matrix_1x1_difval = Matrix();
    matrix_1x1_difval.set(std::vector<std::vector<double>>({{10}})); 
    EXPECT_FALSE(matrix_1x1==matrix_1x1_difval);
    //stejne hodnoty
    EXPECT_TRUE(matrix_1x3 == matrix_1x3_copy);
}

TEST_F(MatrixOperationsTest, MatrixAddition)
{
    //ruzne velikosti
    EXPECT_ANY_THROW(matrix_3x1 + matrix_4x4);
    EXPECT_ANY_THROW(matrix_1x1 + matrix_3x1);
    //stejna velikost
    Matrix expected = Matrix(3,1);
    expected.set(std::vector<std::vector<double>>({{2},{14},{24}}));
    EXPECT_TRUE((matrix_3x1+matrix_3x1)==expected);
    Matrix expected2 = Matrix(1,1);
    expected2.set(std::vector<std::vector<double>>({{8}}));
    EXPECT_TRUE(matrix_1x1 + matrix_1x1 == expected2);
}

TEST_F(MatrixOperationsTest, MatrixMultiplication)
{
    //spatne velikosti - prvni musi mit sloupcu, jako druha radku
    EXPECT_ANY_THROW(matrix_4x4*matrix_1x3);
    EXPECT_ANY_THROW(matrix_1x3 * matrix_1x3);

    //spravne velikosti
    Matrix expected = Matrix();
    expected.set(std::vector<std::vector<double>>({{94}}));
    EXPECT_TRUE((matrix_1x3 * matrix_3x1) == expected);
    Matrix expected2 = Matrix();
    expected2.set(std::vector<std::vector<double>>({{16}}));
    EXPECT_TRUE((matrix_1x1 * matrix_1x1) == expected2);
}
TEST_F(MatrixOperationsTest, MatrixScalarMultiplication)
{
    Matrix expected= Matrix(3,1);
    expected.set(std::vector<std::vector<double>>({{2},{14},{24}}));
    EXPECT_TRUE((matrix_3x1*2) == expected);
    Matrix expected2 = Matrix();
    expected2.set(std::vector<std::vector<double>>({{20}}));
    EXPECT_TRUE((matrix_1x1*5)==expected2);
}

TEST_F(MatrixOperationsTest, MatrixEquationSolve)
{
    //rozdilny pocet prvku prave strany a poctu radku matice
    EXPECT_ANY_THROW(matrix_4x4.solveEquation(std::vector<double>({15.5,4,3,5.6,17})));
    EXPECT_ANY_THROW(matrix_3x1.solveEquation(std::vector<double>({2,5,5})));
    //nectvercova
    EXPECT_ANY_THROW(matrix_1x3.solveEquation(std::vector<double>({3,2,5})));
    //determinant 0
    EXPECT_ANY_THROW(determinant_zero.solveEquation(std::vector<double>({4,5})));
    //spravny vysledek - matice 1x1
    EXPECT_EQ(matrix_1x1.solveEquation(std::vector<double>({8})),std::vector<double>({2}));
    //spravny vysledek - matice 2x2
    EXPECT_EQ(matrix_2x2.solveEquation(std::vector<double>({4,2})),std::vector<double>({0,1}));
    //spravy vysledek - matice 3x3
    EXPECT_EQ(matrix_3x3.solveEquation(std::vector<double>({4,1,2})),std::vector<double>({2, -2, 3}));
    //spravny vysledek - matice 4x4
    EXPECT_EQ(matrix_4x4.solveEquation(std::vector<double>({2,2,2,2})),std::vector<double>({0, 0, 1, 0}));

}
/*** Konec souboru white_box_tests.cpp ***/
