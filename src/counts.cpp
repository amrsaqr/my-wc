//
// Copyright 2024 Amr Saqr
//

#include "counts.h"

void Counts::IncBytes(const unsigned int bytes) { bytes_ += bytes; }

void Counts::IncLines(const unsigned int lines) { lines_ += lines; }

void Counts::IncWords(const unsigned int words) { words_ += words; }

void Counts::IncChars(const unsigned int chars) { chars_ += chars; }

unsigned int Counts::GetBytes() const { return bytes_; }

unsigned int Counts::GetLines() const { return lines_; }

unsigned int Counts::GetWords() const { return words_; }

unsigned int Counts::GetChars() const { return chars_; }

Counts& Counts::operator+=(const Counts& rhs) {
  this->IncBytes(rhs.GetBytes());
  this->IncLines(rhs.GetLines());
  this->IncWords(rhs.GetWords());
  this->IncChars(rhs.GetChars());
  return *this;
}
