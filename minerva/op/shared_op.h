#pragma once

#include <sstream>
#include "shared.h"
#include "closure.h"

namespace minerva {

class MatMultOp : public SharedComputeFn {
 public:
  std::vector<NVector<Chunk>> Expand(std::vector<NVector<Chunk>> inputs) {
    NVector<Chunk> a = inputs[0];
    NVector<Chunk> b = inputs[1];
    // validity
    assert(a.Size(1) == b.Size(0));
    int m = a.Size(0);
    int n = b.Size(1);
    int k = a.Size(1);
    // matmult
    NVector<Chunk> c({m, n});
    for(int i = 0 ; i < m; ++i) {
      for(int j = 0; j < n; ++j) {
        int row = a[{i, 0}].Size(0);
        int col = b[{0, j}].Size(1);
        c[{i, j}] = Chunk::Constant({row, col}, 0.0);
        for(int l = 0; l < k; ++l) {
          c[{i, j}] += a[{i, l}] * b[{l, j}];
        }
      }
    }
    return {c};
  }
  std::string Name() const {
    return "*";
  }
};

class RandnOp : public SharedDataGenFn, public ClosureTrait<RandnClosure> {
 public:
  std::vector<NVector<Chunk>> Expand(const Scale& size) {
    //TODO
    return std::vector<NVector<Chunk>>();
  }
  std::string Name() const {
    return ":randn";
  }
};

class FillOp : public SharedDataGenFn, public ClosureTrait<FillClosure> {
 public:
  std::vector<NVector<Chunk>> Expand(const Scale& size) {
    //TODO
    return std::vector<NVector<Chunk>>();
  }
  std::string Name() const {
    std::stringstream ss;
    ss << ":const=" << closure.val;
    return ss.str();
  }
};

class TransOp : public SharedComputeFn {
 public:
  std::vector<NVector<Chunk>> Expand(std::vector<NVector<Chunk>> inputs) {
    //TODO
    return std::vector<NVector<Chunk>>();
  }
  std::string Name() const {
    return "trans";
  }
};

class ElewiseOp : public SharedComputeFn,
  public ClosureTrait<ElewiseClosure> {
 public:
  std::vector<NVector<Chunk>> Expand(std::vector<NVector<Chunk>> inputs) {
    //TODO
    return std::vector<NVector<Chunk>>();
  }
  std::string Name() const {
    switch(closure.type) {
      case EXP:      return "exp";
      case LN:       return "ln";
      case SIGMOID:  return "sigmoid";
      case NEGATIVE: return "-";
    };
  }
};

class ArithmicOp : public SharedComputeFn,
  public ClosureTrait<ArithmicClosure> {
 public:
  std::vector<NVector<Chunk>> Expand(std::vector<NVector<Chunk>> inputs) {
    //TODO
    return std::vector<NVector<Chunk>>();
  }
  std::string Name() const {
    switch(closure.type) {
      case ADD:   return "+";
      case SUB:   return "-";
      case MULT:  return ".*";
      case DIV:   return "./";
    };
  }
};

class ArithmicConstOp : public SharedComputeFn,
  public ClosureTrait<ArithmicConstClosure> {
 public:
  std::vector<NVector<Chunk>> Expand(std::vector<NVector<Chunk>> inputs) {
    //TODO
    return std::vector<NVector<Chunk>>();
  }
  std::string Name() const {
    std::stringstream ss;
    if(closure.side == 0) { // left
      ss << closure.val;
    }
    switch(closure.type) {
      case ADD:   ss << "+"; break;
      case SUB:   ss << "-"; break;
      case MULT:  ss << ".*"; break;
      case DIV:   ss << "./"; break;
    };
    if(closure.side == 1) { // right
      ss << closure.val;
    }
    return ss.str();
  }
};

} // end of namespace minerva