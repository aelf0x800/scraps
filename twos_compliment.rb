def twos_compliment(a, b)
	fa = (a ^ 0xff) + 0x1
	fb = (b ^ 0xff) + 0x1
	puts fa.to_s(2)
	return fa + fb
end

puts(twos_compliment(-3, 5).to_s(2))