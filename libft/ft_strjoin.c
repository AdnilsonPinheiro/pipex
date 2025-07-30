/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpinhei <adpinhei@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:46:02 by adpinhei          #+#    #+#             */
/*   Updated: 2025/07/30 18:24:35 by adpinhei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	dest = (char *)malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len_s1 + 1);
	ft_strlcat(dest, s2, len_s2 + len_s1 + 1);
	return (dest);
}
