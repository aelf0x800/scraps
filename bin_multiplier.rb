def bin_multiplier(a, b)
	mul = a << (b / 2)
	mul /= 2 if b % 2 != 0
	return mul
end

if ARGV.length != 2 then
	puts("usage: bin_multiplier [a] [b]")
	exit(1)
end

a = ARGV[0].to_i
b = ARGV[1].to_i
puts(bin_multiplier(a, b).to_s(2))