set pagination off

set $cnt = 1

break range.c:63
	command 1
	if $cnt > 27 & $cnt < 36
		printf "@@@ start = %d, end = %d, step = %d, element = %d\n", I.start, I.stop, I.step, I.curr_value
	end
	set $cnt = $cnt + 1
	continue
end

run -100 100 3
quit