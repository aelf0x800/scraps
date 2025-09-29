def twos_compliment(a, b)
	fa = (a ^ 0xff) + 0x1
	fb = (b ^ 0xff) + 0x1
	return fa + fb
end

if ARGV.length != 2 then
	puts("usage: twos_compliment [a] [b]")
end

a = ARGV[0].to_i
b = ARGV[1].to_i
puts(twos_compliment(a, b).to_s(2))