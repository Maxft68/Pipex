/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdsiurds <mdsiurds@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:21:18 by mdsiurds          #+#    #+#             */
/*   Updated: 2025/03/18 14:21:36 by mdsiurds         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char *s4;
	char *s5;
	
	s4 = ft_strjoin(s1, s2);
	s5 = ft_strjoin(s4, s3);
	free(s4);
	
	return(s5);
}
