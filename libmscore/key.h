//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2002-2014 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __KEY__H__
#define __KEY__H__

namespace Ms {

class Xml;
class Score;
class XmlReader;
enum class AccidentalVal : signed char;

//---------------------------------------------------------
//   Key
//---------------------------------------------------------

enum class Key {
      C_B = -7,
      G_B, D_B, A_B, E_B, B_B, F,   C,
      G,   D,   A,   E,   B,   F_S, C_S,
      MIN = Key::C_B,
      MAX = Key::C_S,
      INVALID = Key::MIN - 1,
      NUM_OF = Key::MAX - Key::MIN + 1,
      DELTA_ENHARMONIC = 12
      };

static inline bool operator<  (Key a, Key b) { return int(a) < int(b); }
static inline bool operator>  (Key a, Key b) { return int(a) > int(b); }
static inline bool operator>  (Key a, int b) { return int(a) > b; }
static inline bool operator<  (Key a, int b) { return int(a) < b; }
static inline bool operator== (Key a, Key b) { return int(a) == int(b); }
static inline bool operator!= (Key a, Key b) { return int(a) != int(b); }
static inline Key  operator+= (Key& a, const Key& b) { return a = Key(int(a) + int(b)); }
static inline Key  operator-= (Key& a, const Key& b) { return a = Key(int(a) - int(b)); }

//---------------------------------------------------------
//   KeySigEvent
//---------------------------------------------------------

class KeySigEvent {
      Key _key            { Key::C };          // -7 -> +7
      int _customType     { 0 };
      bool _custom        { false };
      bool _invalid       { true };

      void enforceLimits();

   public:
      KeySigEvent() {}
      KeySigEvent(Key);

      bool isValid() const { return !_invalid; }
      bool operator==(const KeySigEvent& e) const;
      bool operator!=(const KeySigEvent& e) const;

      void setKey(Key v);
      void setCustomType(int v);
      void print() const;

      Key key() const            { return _key; }
      int customType() const     { return _customType;     }
      bool custom() const        { return _custom;         }
      bool invalid() const       { return _invalid;        }
      void initFromSubtype(int);    // for backward compatibility
      void initLineList(char*);
      };

//---------------------------------------------------------
//   AccidentalState
///   Contains a state for every absolute staff line.
//---------------------------------------------------------

static const int TIE_CONTEXT = 0x10;

class AccidentalState {
      uchar state[75];    // (0 -- 4) | TIE_CONTEXT

   public:
      AccidentalState() {}
      void init(Key key);
      AccidentalVal accidentalVal(int line) const;
      bool tieContext(int line) const;
      void setAccidentalVal(int line, AccidentalVal val, bool tieContext = false);
      };

struct Interval;
extern Key transposeKey(Key oldKey, const Interval&);


}     // namespace Ms
#endif

