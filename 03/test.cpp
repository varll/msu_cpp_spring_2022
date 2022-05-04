#include "matrix.hpp"
#include "gtest/gtest.h"


TEST(TestMatrix, TestValidCreation){
    Matrix A(1,1), B(4, 1), C(1, 4), D(3, 5);
    
    ASSERT_EQ(A.getRows(), 1);
    ASSERT_EQ(A.getCols(), 1);

    ASSERT_EQ(B.getRows(), 4);
    ASSERT_EQ(B.getCols(), 1);

    ASSERT_EQ(C.getRows(), 1);
    ASSERT_EQ(C.getCols(), 4);

    ASSERT_EQ(D.getRows(), 3);
    ASSERT_EQ(D.getCols(), 5);

}

TEST(TestMatrix, TestIdx){
    Matrix A(3,3);

    for(size_t i = 0; i < A.getCols(); i++){
        for(size_t j = 0; j < A.getRows(); j++){
            A[i][j] = i;
        }
    }

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

    int test_value = A[0][0];
    ASSERT_EQ(test_value, 0);

    test_value = A[2][2];
    ASSERT_EQ(test_value, 2);
}

TEST(TestMatrix, TestMultiplication){
    Matrix A(1, 1), B(4, 1), C(1, 4), D(3, 5);
    A[0][0] = 1;
    for(size_t i = 0; i < B.getRows(); i++){
        for(size_t j = 0; j < B.getCols(); j++){
            B[i][j] = 3;
            C[j][i] = 2;
        }
    }
    for(size_t i = 0; i < D.getRows(); i++){
        for(size_t j = 0; j < D.getCols(); j++){
            D[i][j] = 6;
        }
    }

    A *= 5;
    B *= 3;
    C *= -2;
    D *= 0;

    ASSERT_EQ(A[0][0], 5);
    for(size_t i = 0; i < B.getRows(); i++){
        for(size_t j = 0; j < B.getCols(); j++){
            ASSERT_EQ(B[i][j], 9);
            ASSERT_EQ(C[j][i], -4);
        }
    }
    for(size_t i = 0; i < D.getRows(); i++){
        for(size_t j = 0; j < D.getCols(); j++){
            ASSERT_EQ(D[i][j], 0);
        }
    }
}

TEST(TestMatrix, TestSum){
    Matrix A(3,3), B(3,3), C(3,1), D(3, 1);

    for(size_t i = 0; i < A.getRows(); i++){
        for(size_t j = 0; j < A.getCols(); j++){
            A[i][j] = 3;
            B[i][j] = 7;
        }
    }
    for(size_t i = 0; i < C.getRows(); i++){
        for(size_t j = 0; j < C.getCols(); j++){
            C[i][j] = 3;
            D[i][j] = 1;
        }
    }   

    try{
        A + C;
    }
    catch(std::out_of_range const & err){
        EXPECT_EQ(err.what(), std::string("Wrong dimensions"));
    }

    Matrix test_sum1 = A + B;

    for(size_t i = 0; i < test_sum1.getRows(); i++){
        for(size_t j = 0; j < test_sum1.getCols(); j++){
            ASSERT_EQ(test_sum1[i][j], 10);
        }
    }

    Matrix test_sum2 = C + D;

    for(size_t i = 0; i < test_sum2.getRows(); i++){
        for(size_t j = 0; j < test_sum2.getCols(); j++){
            ASSERT_EQ(test_sum2[i][j], 4);
        }
    }


}

TEST(TestMatrix, TestEq){
    Matrix A(3, 1), B(3, 1), C(1, 3);
    
    for(size_t i = 0; i < A.getRows(); i++){
        for(size_t j = 0; j < A.getCols(); j++){
            A[i][j] = 3;
            B[i][j] = 3;
            C[j][i] = 2;
        }
    }

    ASSERT_TRUE(A == B);
    ASSERT_FALSE(A == C);

    A[0][0] = 0;

    ASSERT_FALSE(A == B);
}

TEST(TestMatrix, TestOutput){
    Matrix A(8,1), B(1, 8), C(1,1), D(4,3);
    std::string A_test_output = {"1\n1\n1\n1\n1\n1\n1\n1"},
                B_test_output = {"1 1 1 1 1 1 1 1"},
                C_test_output = {"1"},
                D_test_output = {"4 4 4\n4 4 4\n4 4 4\n4 4 4"};
    for(size_t i = 0; i < A.getRows(); i++){
        for(size_t j = 0; j < A.getCols(); j++){
            A[i][j] = 1;
            B[j][i] = 1;
        }
    }
    C[0][0] = 1;
    for(size_t i = 0; i < D.getRows(); i++){
        for(size_t j = 0; j < D.getCols(); j++){
            D[i][j] = 4;
        }
    }

    testing::internal::CaptureStdout();
    std::cout<<A; 
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(A_test_output, output);

    testing::internal::CaptureStdout();
    std::cout<<B; 
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(B_test_output, output);

    testing::internal::CaptureStdout();
    std::cout<<C; 
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(C_test_output, output);

    testing::internal::CaptureStdout();
    std::cout<<D; 
    output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(D_test_output, output);
     
}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
