#include "matrix.hpp"
#include "gtest/gtest.h"


TEST(TestMatrix, TestValidCreation){
    Matrix A(1,1);
    A[0][0] = 0;
    
    ASSERT_EQ(A.getCols(), 1);
    ASSERT_EQ(A.getRows(), 1);
    ASSERT_EQ(A[0][0], 0);
}

TEST(TestMatrix, TestIdx){
    Matrix A(3,3);

    try{
        A[4][3];
    }
    catch(std::out_of_range const & err){
        EXPECT_EQ(err.what(), std::string("Out of range"));
    }

    try{
        A[3][4];
    }
    catch(std::out_of_range const & err){
        EXPECT_EQ(err.what(), std::string("Out of range"));
    }
}

TEST(TestMatrix, TestMultiplication){
    Matrix A(3,3);

    for(size_t i = 0; i < A.getCols(); i++){
        for(size_t j = 0; j < A.getRows(); j++){
            A[i][j] = 3;
        }
    }

    A *= 5;

    for(size_t i = 0; i < A.getCols(); i++){
        for(size_t j = 0; j < A.getRows(); j++){
            ASSERT_EQ(A[i][j], 15);
        }
    }

}

TEST(TestMatrix, TestSum){
    Matrix A(3,3), B(3,3), C(3,1);

    for(size_t i = 0; i < A.getRows(); i++){
        for(size_t j = 0; j < A.getCols(); j++){
            A[i][j] = 3;
            B[i][j] = 7;
        }
    }
    for(size_t i = 0; i < C.getRows(); i++){
        for(size_t j = 0; j < C.getCols(); j++){
            C[i][j] = 3;
        }
    }   

    try{
        A + C;
    }
    catch(std::out_of_range const & err){
        EXPECT_EQ(err.what(), std::string("Wrong dimensions"));
    }

    Matrix D = A + B;

    for(size_t i = 0; i < D.getCols(); i++){
        for(size_t j = 0; j < D.getRows(); j++){
            ASSERT_EQ(D[i][j], 10);
        }
    }

}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
