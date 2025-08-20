#include <gtest/gtest.h>
import kaleidoscope;

class GlobalEnv : public ::testing::Environment {
protected:
    void SetUp() override {
        Kaleidoscope::initLLVM();
        Kaleidoscope::Parser::defaultBinopPrecedenceCtor();
    }
};

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::AddGlobalTestEnvironment(new GlobalEnv);
    return RUN_ALL_TESTS();
}
