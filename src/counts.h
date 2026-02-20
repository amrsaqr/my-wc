//
// Copyright 2024 Amr Saqr
//

#ifndef COUNTS_H_
#define COUNTS_H_

class Counts {
 public:
  Counts() = default;
  Counts(unsigned int bytes, unsigned int lines, unsigned int words, unsigned int chars);

  void IncBytes(unsigned int = 1);
  void IncLines(unsigned int = 1);
  void IncWords(unsigned int = 1);
  void IncChars(unsigned int = 1);

  [[nodiscard]] unsigned int GetBytes() const;
  [[nodiscard]] unsigned int GetLines() const;
  [[nodiscard]] unsigned int GetWords() const;
  [[nodiscard]] unsigned int GetChars() const;

  Counts& operator+=(const Counts& rhs);

 private:
  unsigned int bytes_{0};
  unsigned int lines_{0};
  unsigned int words_{0};
  unsigned int chars_{0};
};

#endif  // COUNTS_H_
