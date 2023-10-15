set pagination off

break range.c:63 if I.curr_value % 5 == 0
	command 1
	printf "@@@ start = %d, end = %d, step = %d, element = %d\n", I.start, I.stop, I.step, I.curr_value
	continue
end

run 1 12
quit