/*********************************************************************************************************
**
**                                    中国软件开源组织
**
**                                   嵌入式实时操作系统
**
**                                       SylixOS(TM)
**
**                               Copyright  All Rights Reserved
**
**--------------文件信息--------------------------------------------------------------------------------
**
** 文   件   名: gjb_netrel.c
**
** 创   建   人: Han.Hui (韩辉)
**
** 文件创建日期: 2016 年 04 月 13 日
**
** 描        述: GJB7714 扩展接口网络相关部分.
*********************************************************************************************************/
#define  __SYLIXOS_KERNEL
#include "SylixOS.h"
/*********************************************************************************************************
  裁剪支持
*********************************************************************************************************/
#if (LW_CFG_POSIX_EN > 0) && (LW_CFG_GJB7714_EN > 0)
#include "../include/px_gjbext.h"
#if LW_CFG_NET_EN > 0
#include "socket.h"
#include "net/if.h"
/*********************************************************************************************************
** 函数名称: ifconfig
** 功能描述: 设置指定网卡 IP.
** 输　入  : name          网卡名
**           ip            ip 地址
**           netmask       子网掩码
** 输　出  : ERROR or OK
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
int  ifconfig (char *name, char *ip, char *netmask)
{
    int             sock;
    struct ifreq    req;
    struct in_addr  ipaddr;
    struct in_addr  mskaddr;
    
    if (!name || !ip || !netmask) {
        errno = EINVAL;
        return  (PX_ERROR);
    }
    
    if (!inet_aton(ip, &ipaddr)) {
        errno = EINVAL;
        return  (PX_ERROR);
    }
    
    if (!inet_aton(netmask, &mskaddr)) {
        errno = EINVAL;
        return  (PX_ERROR);
    }
    
    lib_strlcpy(req.ifr_name, name, IFNAMSIZ);
    req.ifr_addr.sa_family = AF_INET;
    
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        return  (PX_ERROR);
    }
    
    ((struct sockaddr_in *)&req.ifr_addr)->sin_addr = ipaddr;
    if (ioctl(sock, SIOCSIFADDR, &req)) {
        close(sock);
        return  (PX_ERROR);
    }
    
    ((struct sockaddr_in *)&req.ifr_netmask)->sin_addr = mskaddr;
    if (ioctl(sock, SIOCSIFNETMASK, &req)) {
        close(sock);
        return  (PX_ERROR);
    }
    
    close(sock);
    return  (ERROR_NONE);
}
/*********************************************************************************************************
** 函数名称: if_show
** 功能描述: 显示网络接口信息.
** 输　入  : NONE
** 输　出  : NONE
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
void  if_show (void)
{
    lib_system("ifconfig");
}
/*********************************************************************************************************
** 函数名称: mbuf_show
** 功能描述: 显示网络缓冲区信息.
** 输　入  : NONE
** 输　出  : NONE
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
void  mbuf_show (void)
{
    lib_system("netstat -s");
}
/*********************************************************************************************************
** 函数名称: udp_show
** 功能描述: 显示 UDP 信息.
** 输　入  : NONE
** 输　出  : NONE
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
void  udp_show (void)
{
    lib_system("netstat -u");
}
/*********************************************************************************************************
** 函数名称: tcp_show
** 功能描述: 显示 TCP 信息.
** 输　入  : NONE
** 输　出  : NONE
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
void  tcp_show (void)
{
    lib_system("netstat -t");
}
/*********************************************************************************************************
** 函数名称: routes_show
** 功能描述: 显示路由信息.
** 输　入  : NONE
** 输　出  : NONE
** 全局变量: 
** 调用模块: 
                                           API 函数
*********************************************************************************************************/
LW_API 
void  routes_show (void)
{
    lib_system("route");
}

#endif                                                                  /*  LW_CFG_NET_EN > 0           */
#endif                                                                  /*  LW_CFG_POSIX_EN > 0         */
                                                                        /*  LW_CFG_GJB7714_EN > 0       */
/*********************************************************************************************************
  END
*********************************************************************************************************/
