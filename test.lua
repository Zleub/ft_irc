i = 0
pool = '0123456789'

os.execute('nc localhost 6667')

while 42 do
	if i > 10000000 then
		str = ''
		msg_size = math.random(80)
		for i=1,msg_size do
			nb = math.random(pool:len())
			if pool:sub(nb, nb) == '\n' then j = j + 1 end
			str = str..pool:sub(nb, nb)
		end
		print(str)
		-- os.execute('echo '..str)
		i = 0
	end
	i = i + 1
end
