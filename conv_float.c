/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_float.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/17 15:41:31 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/19 20:59:19 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <limits.h> 
#include "libft.h"
#include <float.h>

int isinf(double x) 
{
	int inf = 0x7F800000;
	double infinity = 1e305;
	int nan = 0x7F800001;
	return (x == *(float*)&inf || x == *(float*)&nan || x > infinity);
}


char *d_str(double n)
{
	int i;
	char *res;
	float tmp;
	float diff;

	i = 0;
	while (i < 124)
	{
		tmp = n;
		n *= (double)n - (int)tmp * ft_pow(10, 7);
		if (isinf(n))
			break;
		//diff = n - 
		//printf("vvvv : %lu\n", (long int)(tmp - )));

		//res = ft_strjoin(res, ft_itoa(n / ft_pow(10, i * 20)));
		//n -= (int)(n * ft_pow(10, 8));
		i++;
	}
	printf("my value : %f\n", n);

	return (res);
}

char	*conv_float(unsigned int n, t_info *info)
{
	
}

int main(void) {
	double f = 0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000646844488646464446454884464346843489561103546130310316512316;
	float res = 0;
	double diff = 0;
	double diff_2 = 0;
	char *res_str;
	int begin = 0;
	int k = 0;
	//char binaryRepresentation[sizeof f * CHAR_BIT];
	//f_tob(binaryRepresentation, f);
	//printf("%s\n", binaryRepresentation);
	//res = calc_float(binaryRepresentation);
	begin = (int)res; 
	diff = (double)f - begin;
	printf("\nPRINTF : %.1100f\n", diff); // ULONG = 20. printf max p = 52. LONG = 19 * 3 = 57 -- gerer precision jusqu a 1100 digit. 
	// 19 * 64 = 1216. ca X124 : f * ft_pow(10, 8); f = f*ft_pow(10, 8); 
	// res = ft_strjoin(res, ft_itoa(ft_pow(10, 8)))
	//printf("DIFF : %f\n", (double)(diff));
	//printf("DIFF_2 : %f\n", diff * 100000000000000000);

	diff_2 = f - begin;
	res_str = ft_itoa(begin);
	//printf("%s\n", (char*)diff);
	res_str = ft_strjoin(res_str, d_str(diff));
	printf("%s\n", res_str);
	//res_str = ft_strjoin(res_str, );
	//printf("%.20f\n", );
	//print(binaryRepresentation, 32);
}
