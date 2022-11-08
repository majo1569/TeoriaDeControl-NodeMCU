PROGRAM Lab2
  VAR
    micro AT %IW0 : INT;
    led1 AT %QX0.1 : BOOL := 0;
    led2 AT %QX0.2 : BOOL := 0;
    led3 AT %QX0.3 : BOOL := 0;
    rele AT %QX0.0 : BOOL := 0;
  END_VAR
  VAR
    TP1 : TP;
    TP2 : TP;
    TP3 : TP;
    TP4 : TP;
    _TMP_LE14_OUT : BOOL;
    _TMP_LE3_OUT : BOOL;
    _TMP_LE6_OUT : BOOL;
  END_VAR

  _TMP_LE14_OUT := LE(micro, 600);
  TP1(IN := _TMP_LE14_OUT, PT := T#10s);
  rele := TP1.Q;
  TP3(IN := _TMP_LE14_OUT, PT := T#3s);
  led3 := TP3.Q;
  _TMP_LE3_OUT := LE(micro, 800);
  TP2(IN := _TMP_LE3_OUT, PT := T#6s);
  led2 := TP2.Q;
  _TMP_LE6_OUT := LE(micro, 1000);
  TP4(IN := _TMP_LE6_OUT, PT := T#9s);
  led1 := TP4.Q;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Lab2;
  END_RESOURCE
END_CONFIGURATION
