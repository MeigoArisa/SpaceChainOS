;/*********************************************************************************************************
;**
;**                                    �й�������Դ��֯
;**
;**                                   Ƕ��ʽʵʱ����ϵͳ
;**
;**                                       SylixOS(TM)
;**
;**                               Copyright  All Rights Reserved
;**
;**--------------�ļ���Ϣ--------------------------------------------------------------------------------
;**
;** ��   ��   ��: sparcMpCoreAsm.S
;**
;** ��   ��   ��: Xu.Guizhou (�����)
;**
;** �ļ���������: 2017 �� 7 �� 26 ��
;**
;** ��        ��: SPARC ��ϵ���ܶ�˽ӿ�����.
;*********************************************************************************************************/

#ifndef ASSEMBLY
#define ASSEMBLY 1
#endif

#include <arch/assembler.h>

#if LW_CFG_SMP_EN > 0

    FILE_BEGIN()
    
    IMPORT_LABEL(bspMpInt)
    
    EXPORT_LABEL(sparcSpinLock)
    EXPORT_LABEL(sparcSpinTryLock)
    EXPORT_LABEL(sparcSpinUnlock)
    EXPORT_LABEL(archMpCur)
    EXPORT_LABEL(archMpInt)
    
    WEAK(sparcSpinLock)
    WEAK(sparcSpinTryLock)
    WEAK(sparcSpinUnlock)
    WEAK(archMpCur)
    WEAK(archMpInt)

;/*********************************************************************************************************
;  ������
;*********************************************************************************************************/

FUNC_DEF(sparcSpinLock)
LINE_LABEL(sl_retry)
    LDSTUB  [%o0] , %g1                                                 ;/*  ԭ�Ӽ���ԭֵ��д 1          */
    TST     %g1
    BE      sl_out
    NOP
LINE_LABEL(sl_loop)
    LDUB    [%o0] , %g1                                                 ;/*  ����д̫���                */
    TST     %g1
    BNE     sl_loop
    NOP
    BA,a    sl_retry
    NOP
LINE_LABEL(sl_out)
    RETL
    NOP
    FUNC_END(sparcSpinLock)

FUNC_DEF(sparcSpinTryLock)
    LDSTUB  [%o0] , %o0                                                 ;/*  ԭ�Ӽ���ԭֵ��д 1          */
    RETL
    NOP
    FUNC_END(sparcSpinTryLock)

FUNC_DEF(sparcSpinUnlock)
    STUB    %g0 , [%o0]                                                 ;/*  д 0                        */
    RETL
    NOP
    FUNC_END(sparcSpinUnlock)

;/*********************************************************************************************************
;  ��õ�ǰ�� ID
;*********************************************************************************************************/

FUNC_DEF(archMpCur)
    READ_CPUID(%o0)
    RETL
    NOP
    FUNC_END(archMpCur)

;/*********************************************************************************************************
;  ����һ�κ˼��ж�
;*********************************************************************************************************/

FUNC_DEF(archMpInt)
    BA      bspMpInt
    NOP
    FUNC_END(archMpInt)
    
    FILE_END()

#endif
;/*********************************************************************************************************
;  END
;*********************************************************************************************************/