#ifndef SEMES_RANGE_HPP
#define SEMES_RANGE_HPP

struct Range {
  Range() = default;
  Range(int x, int y);
  
  int min;
  int max;
};

#endif //SEMES_RANGE_HPP
