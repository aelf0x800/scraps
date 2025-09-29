def vigenere(key, msg)
	key = key.upcase.gsub(/\W/, "")
	msg = msg.upcase.gsub(/\W/, "")
	emsg = ""
	[key.length, msg.length].min.times do |i|
		ltr = msg[i].ord + key[i].ord - 'A'.ord
		ltr = 'A'.ord + (ltr - 'Z'.ord - 1) if ltr > 'Z'.ord
		emsg << ltr
	end
	return emsg
end

puts(vigenere("ZETABYTESZ", "Hello World!"))