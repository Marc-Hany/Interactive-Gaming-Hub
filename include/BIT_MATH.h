/*
 * BIT_MATH.h
 *
 *  Created on: Aug 14, 2023
 *      Author: mostafa.mohammady
 */

#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define   SET_BIT(Var , Bit_num)      Var|=(1<<Bit_num)
#define   CLR_BIT(Var , Bit_num)      Var&=(~(1<<Bit_num))
#define   TOGGLE_BIT(Var , Bit_num)   Var^=(1<<Bit_num)
#define   GET_BIT(Var , Bit_num)      ((Var>>Bit_num)&1)





#endif /* BIT_MATH_H_ */
