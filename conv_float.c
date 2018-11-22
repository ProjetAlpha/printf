/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   conv_float.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/17 15:41:31 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/22 08:35:26 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include <stdio.h>

int isinf(double x) 
{
	int inf = 0x7F800000;
	double infinity = 1e305;
	int nan = 0x7F800001;
	return (x == *(float*)&inf || x == *(float*)&nan || x > infinity);
}


int n_tu(int number, int count)
{
	int result = 1;
	while(count-- > 0)
		result *= number;

	return result;
}

int		calc_right(double n)
{
	long long int number;
	int length2;
	double number2;

	number = n;
	length2 = 0;
	number2 = n;
	while((number2 - (double)number) != 0.0 && !((number2 - (double)number) < 0.0))
	{
		number2 = n * (n_tu(10.0, length2 + 1));
		number = number2;
		length2++;
	}
	return (length2);
}

static	void	round_str(char *str, int prec, int calc_r)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] && str[i] == '.')
		i++;
	i+= calc_r - 1;
	if (str[i] && str[i + 1] > str[i])
	   str[i] = str[i] + 1;
	i++;
	while (str[i])
	{
		str[i] = '0';
		i++;
	}
}


static int		check_prec(char *str, int prec, int calc_r)
{
	int i;
	
	i = 0;	
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] && str[i] == '.')
		i++;
	i += calc_r + 1;
	while (str[i] && i < prec - calc_r + 1)
	{
		if (str[i] && str[i + 1] < str[i])
			return (i + 1);
		i++;
	}
	return (0);
}

static void get_prec(char *str, int calc_r, int prec)
{	
	if (check_prec(str, prec, calc_r) != 0)
		;	
	else
		round_str(str, prec, calc_r);	
}

int		get_len(double n)
{
	int len;

	len = (n > 1) ? 0 : 1;
	while (n >  1)
	{
			len++;
	        n /= 10;
	}
	return (len);
}


char	*conv_float(double n, t_info *info)
{
	int left;
	char *ret;
	int len;
	char *dest;
	int i;
	int tmp_2;
	int calc_r;
	double tmp;
	int d_i;
	double diff;
	int j;
	int r_len;
	int l_d;
	int prec;
	int neg;

	r_len = 0;
	ret = ft_strnew(0);
	tmp = 0;
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	calc_r = calc_right(n);
	l_d = get_len(n);
	if (info->prec == 0 && calc_r < 6)
		tmp_2 = 6 - calc_r;
	else if (info->prec == 0 && calc_r > 6)
		tmp_2 = calc_r;
	prec = info->prec > 0 ? info->prec + 1 : tmp_2 + calc_r + 1;
	d_i = 0;
	j = 0;
	len = 0;
	i = 0;
	left = (int)n;
	diff = (double)n - left; // = 0.506456. 0.506 5.06 50.6 - 5 44.4 
	info->u_arg = left;
	ret	= ft_strjoin(ret, conv_ubase(info, 10, get_nbr_len(info, 10, 1)));
	len = 500;
	if (!(dest = malloc(sizeof(char) * len + 1)))
		return (NULL);	
	j = 0;
	while (n >= 1.0)
	{
		n/=10;
		++j;	
	}
	while (n < 0.1)
	{
		r_len++;
		n *= 10;
		--j;
	}
	left = (int)n;
	tmp = (double)n;
	if (info->prec == 0 && (calc_r > 6 ||  l_d > 6))
		prec = calc_r + l_d + 2;
	//printf("PREC : %d\n", calc_r + );
	while (prec--)
	{
		d_i = tmp * 10;
		if (i == j)
			dest[i++] = '.';
		dest[i] = d_i + '0';
		tmp = tmp * 10 - d_i;
		i++;
	}
	dest[i] = '\0';
	//printf("RESSS : %s\n", get_prec(dest, calc_r, info->prec > 0 ? info->prec + 1 : tmp_2 + calc_r + 1));
	//printf("DEST : %s\n", dest);
	info->neg = 0;
	if (neg == 1)
	{
		write(1, "-", 1);
		info->neg++;
	}
	if (!(info->prec == 0 && (calc_r > 6 ||  l_d > 6)))
		get_prec(dest, calc_r, info->prec > 0 ? info->prec + 1 : tmp_2 + calc_r + 1);
	return (dest);
}

/*int main(void) {
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
begin = (unsigned long)res;
diff = (double)f - begin;
//printf("\nPRINTF : %.1100f\n", diff); // ULONG = 20. printf max p = 52. LONG = 19 * 3 = 57 -- gerer precision jusqu a 1100 digit. 
// 19 * 64 = 1216. ca X124 : f * ft_pow(10, 8); f = f*ft_pow(10, 8); 
// res = ft_strjoin(res, ft_itoa(ft_pow(10, 8)))
//printf("DIFF : %f\n", (double)(diff));
//printf("DIFF_2 : %f\n", diff * 100000000000000000);

diff_2 = f - begin;
res_str = conv_ubase();
//printf("%s\n", (char*)diff);
res_str = ft_strjoin(res_str, d_str(diff));
printf("%s\n", res_str);
//res_str = ft_strjoin(res_str, );
//printf("%.20f\n", );
//print(binaryRepresentation, 32);
}*/
