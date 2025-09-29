def print_table(table, class_desc, data_desc)
	puts("=" * 33)
	puts("|#{class_desc.ljust 15}|#{data_desc.ljust 15}|")
	puts("=" * 33)
	table.each do |k, v|
		puts("|#{k.to_s.ljust 15}|#{v.to_s.ljust 15}|")
	end
	puts("=" * 33)
end

def print_find_location_of_quarter(cf_table_total, quarter, loc)
	print "Q#{quarter} = "
	case quarter
		when 1 
			print("#{cf_table_total} / 4")
		when 2 
			print("(#{cf_table_total} + 1) / 2")
		when 3 
			print("(3 * #{cf_table_total}) / 4")
	end
	puts(" = #{loc}")
end

def print_quarter_class(quarter, quarter_class)
	puts "Q#{quarter} is in the #{quarter_class} class"
end

def table_interpolate(table, quarter)
	print_table(table, "Class", "Freq")

	# Calculate cumulative frequency
	cf_table = table
	cf_table_prev = nil
	cf_table.each do |k, v|
		cf_table[k] += cf_table[cf_table_prev] if cf_table_prev != nil
		cf_table_prev = k
	end
	cf_table_total = cf_table.values.last
	
	print_table(cf_table, "Class", "Cumu Freq")
	
	# Find location of quarter
	loc = cf_table_total
	case quarter
		when 1 
			loc = loc / 4
		when 2 
			loc = (loc + 1) / 2
		when 3 
			loc = (loc * 3) / 4
	end
	loc += 0.5
	
	print_find_location_of_quarter(cf_table_total, quarter, loc)
	
	# Find the class the quarter is in
	quar_cl = nil
	cf_table.each do |k, v|
		if loc <= cf_table[k] then
			quar_cl = k
			break
		end
	end
	
	print_quarter_class(quarter, quar_cl)
end

data = {
	"6 - 10": 2, 
	"11 - 15": 10,
	"16 - 20": 18,
	"21 - 25": 45,
	"26 - 30": 5
}

table_interpolate(data, 2)