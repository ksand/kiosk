all: kiosk.o getMetar.o getTaf.o logwrite.o getparser.o rtrim.o windfrom.o namegen.c \
	parseZulu.o parseActivity.o parseWind.o parseVisibility.o parsePressure.o \
	parseTemp.o parseRain.o parseRainEnding.o parseSnow.o parseClouds.o \
	parseThunderstorm.o parsePrecip.o parseRapid.o parseReportedTime.o parseValidity.o \
	parseAltimeter.c
	cc -o kiosk kiosk.o getMetar.o getTaf.o logwrite.o getparser.o rtrim.o windfrom.o namegen.c \
		parseZulu.o parseActivity.o parseWind.o parseVisibility.o parsePressure.o \
		parseTemp.o parseRain.o parseRainEnding.o parseSnow.o parseClouds.o \
		parseThunderstorm.o parsePrecip.o parseRapid.o parseReportedTime.o parseValidity.o \
		parseAltimeter.c -lncurses

kiosk.o: kiosk.c
	cc -c -Wunused-variable kiosk.c

getMetar.o: getMetar.c
	cc -c -Wunused-variable getMetar.c

getTaf.o: getTaf.c
	cc -c -Wunused-variable getTaf.c

logwrite.o: logwrite.c
	cc -c -Wunused-variable logwrite.c

mkarray.o: mkarray.c
	cc -c -Wunused-variable mkarray.c

rtrim.o: rtrim.c
	cc -c -Wunused-variable rtrim.c

windfrom.o: windfrom.c
	cc -c -Wunused-variable windfrom.c

namegen.o: namegen.c
	cc -c -Wunused-variable namegen.c

getparser.o: getparser.c
	cc -c -Wunused-variable getparser.c

parseZulu.o: parseZulu.c
	cc -c -Wunused-variable parseZulu.c

parseActivity.o: parseActivity.c
	cc -c -Wunused-variable parseActivity.c

parseWind.o: parseWind.c
	cc -c -Wunused-variable parseWind.c

parseVisibility.o: parseVisibility.c
	cc -c -Wunused-variable parseVisibility.c

parseTemp.o: parseTemp.c
	cc -c -Wunused-variable parseTemp.c

parseRain.o: parseRain.c
	cc -c -Wunused-variable parseRain.c

parseRainEnding.o: parseRainEnding.c
	cc -c -Wunused-variable parseRainEnding.c

parseSnow.o: parseSnow.c
	cc -c -Wunused-variable parseSnow.c

parseClouds.o: parseClouds.c
	cc -c -Wunused-variable parseClouds.c

parsePressure.o: parsePressure.c
	cc -c -Wunused-variable parsePressure.c

parseThunderstorm.o: parseThunderstorm.c
	cc -c -Wunused-variable parseThunderstorm.c

parsePrecip.o: parsePrecip.c
	cc -c -Wunused-variable parsePrecip.c

parseRapid.o: parseRapid.c
	cc -c -Wunused-variable parseRapid.c

parseReportedTime.o: parseReportedTime.c
	cc -c -Wunused-variable parseReportedTime.c

parseValidity.o: parseValidity.c
	cc -c -Wunused-variable parseValidity.c

parseAltimeter.o: parseAltimeter.c
	cc -c -Wunused-variable parseAtimeter.c


