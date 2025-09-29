if ARGV.length != 2 then
	puts("usage: as [tc/b/d/x] [value]")
	exit(1)
end

case ARGV[0]
	when "tc"
		puts(((ARGV[1].to_i ^ 0xff) + 0x1).to_s(2))
	when "b"
		puts(ARGV[1].to_i.to_s(2))
	when "d"
		puts(ARGV[1].to_i.to_s(10))
	when "x"
		puts(ARGV[1].to_i.to_s(16))
end