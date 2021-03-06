/**
This is a C Implementation of the Zorro Cipher designed by Gerard et al.

The MIT License (MIT)

Copyright (c) 2015 Christian Walter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

/**
 * One complete Encryption of the zorro cipher
 * @param  statePointer Pointer to the state
 * @param  key			Pointer to the key
 * @return              No return value
 */


void zorroCompleteEnc(uint8_t * state, uint8_t * key);

/**
 * One complete Decryption of the zorro cipher
 * @param  statePointer Pointer to the state
 * @param  key			Pointer to the key
 * @return              No return value
 */

void zorroOneRoundEnc(uint8_t *state, uint8_t round);

void zorroCompleteDec(uint8_t * state, uint8_t * key);

/**
 * First 19 rounds of encryption
 * @param state Pointer to the state
 * @param key   Pointer to the key
 */
int zorro19RoundEnc(uint8_t * state, uint8_t * state2, uint8_t * key);

void zorroOneRoundDec(uint8_t * state, uint8_t round);

