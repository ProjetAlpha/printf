/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   printf.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/29 18:40:57 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/07 20:35:27 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef PRINTF_H

# define PRINTF_H


# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

typedef struct		s_info
{
	int width;
	int prec;
	long long int i_arg;
	int t_len;
	int length;
	int flag;
	int	skip;
	int extra[7];
	int pos[2];
	struct s_info *next;
}					t_info;

# define FLAGS "sSpdDioOuUxXcC"
# define U_IM 4294967296

enum pos{START = 0, END = 1};

//enum length{P_CHAR, CHAR, L_INT, P_INT, C_WINT, S_WCHAR, LL_INT, LLP_INT, INT_M, UINT_M, SIZE_T, SSIZE_T};
enum length{H = 1, HH = 2, L = 3, LL = 4, J = 5, Z = 6};

enum extra{H_TAG = 1, ZERO = 2, MINUS = 3, PLUS = 4, PERCENT = 5, SPACE = 6};

typedef enum flags{S = 1, LS = 2, P = 3, D = 4, LD = 5,
		I = 6, O = 7, LO = 8, U = 9, LU = 10, X = 11, LX = 12, C = 13, LC = 14} values;

values allValues[] = {S, LS, P, D, LD,
		I, O, LO, U, LU, X, LX, C, LC};


#endif
