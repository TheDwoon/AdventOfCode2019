#include "pch.h"
#include "../AdventOfCode/IntProcessor.cpp"

TEST(IntProcessor, OP_ADD) {
  int memory[] = {1101, 12, 13, 0, 99};

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt";
  EXPECT_EQ(proc.getMemory()[0], 25);
}

TEST(IntProcessor, OP_MULT) {
  int memory[] = { 1102, 2, 3, 0, 99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(proc.getMemory()[0], 6);
}

TEST(IntProcessor, OP_INPUT) {
  int memory[] = { 3, 0, 99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc << 1337;
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(proc.getMemory()[0], 1337);
}

TEST(IntProcessor, OP_OUTPUT) {
  int memory[] = { 104, 42, 99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc.runProgram();

  int64_t procOutput = 0;
  proc >> procOutput;

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(procOutput, 42);
}

TEST(IntProcessor, OP_JUMP_IF_TRUE) {
  int memory[] = { 1105, 2, 4, 99, 3, 0, 99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc << 42;
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(proc.getMemory()[0], 42);
}

TEST(IntProcessor, OP_JMP_IF_FALSE) {
  int memory[] = { 1106, 0, 4, 99, 3, 0, 99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc << 42;
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(proc.getMemory()[0], 42);
}

TEST(IntProcessor, OP_LESS_THEN) {
  int memory[] = { 1107, 0, 4, 0, 99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(proc.getMemory()[0], 1);
}

TEST(IntProcessor, OP_EQUALS) {
  int memory[] = { 1108, 4, 4, 0, 99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(proc.getMemory()[0], 1);
}

TEST(IntProcessor, OP_MODIFY_RELATIVE_BASE) {
  int memory[] = { 109, 4, 99};

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(proc.getRelativeBase(), proc.getMemory() + 4);
}

TEST(IntProcessor, OP_HALT) {
  int memory[] = { 99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);  
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";  
}

TEST(IntProcessor, resolveRead) {
  int memory[] = {
    109, 4, // modify relative base
    4, 0,   // output value with absolute addressing
    104, 42, // output value imidiate value
    204, 0, // output value with relative addressing
    99 };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";

  int64_t out;
  proc >> out;
  EXPECT_EQ(out, 109);
  proc >> out;
  EXPECT_EQ(out, 42);
  proc >> out;
  EXPECT_EQ(out, 104);
}

TEST(IntProcessor, resolveWrite) {
  int memory[] = {
    109, 92,  // modify relative base
    109, 4,   // modify relative base
    109, -2,  // modify relative base
    3, 100,   // input value with absolute addressing    
    203, 7,   // input value with relative addressing
    99        // halt processor
  };

  IntProcessor proc(memory, sizeof(memory) / sizeof(int), 128);
  proc << 42 << 1337;
  proc.runProgram();

  EXPECT_TRUE(proc.isHalted()) << "Processor did not halt!";
  EXPECT_EQ(proc.getMemory()[100], 42);
  EXPECT_EQ(proc.getMemory()[101], 1337);
}
