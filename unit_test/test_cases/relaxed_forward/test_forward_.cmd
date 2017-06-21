rem %1 - test numer
echo //================================================================================================================================================
echo // test %1 [FORWARD RESOLVER DUMPER]
echo //================================================================================================================================================
%gieidl_bin% --backend fwddump --input-file=data\test%1.in --output-file test%1.this.out 2>test%1.forward.log
fc data\test%1.forward.out test%1.this.out
del test%1.this.out