class TraderPlusLogger
{
	FileHandle g_FileHandle;

	void TraderPlusLogger() {
		g_FileHandle =  CreateNewLogFile();
	}

	void ~TraderPlusLogger() {
		CloseFile(g_FileHandle);
	}

	FileHandle CreateNewLogFile()	{
		string filePath = TRADERPLUS_LOGGER_DIR_SERVER + TRADERPLUS_LOGGER_PREFIX_SERVER + "_" + GenerateFullTimeStamp() + ".log";
		//Check the file does not already exist ... fuck knows how it would
		g_FileHandle = OpenFile(filePath, FileMode.WRITE);

		//File created
		if (g_FileHandle != 0) {
			FPrintln(g_FileHandle, "Creation Time: " + GenerateFullTimeStamp());
			return g_FileHandle;
		}
		return NULL;
	}

	void Log(string content) {
		string timeStamp = GenerateShortTimeString();
		FPrintln(g_FileHandle, timeStamp + " | " + content);
	}

	void LogError(string content) {
		Log("[ERROR] " + content);
	}

	void LogInfo(string content) {
		Log("[INFO] " + content);
	}

	string GenerateShortDateString() {
		int year, month, day;
		GetYearMonthDay(year, month, day);
		string ret = "" + year + "_" + month + "_" + day;
		return ret;
	}

	string GenerateShortTimeString() {
		int hour, minute, second;
		GetHourMinuteSecond(hour, minute, second);
		string ret = "" + hour + "-" + minute + "-" + second;
		return ret;
	}

	string GenerateFullTimeStamp() {
		string dateStr = GenerateShortDateString();
		string timeStr = GenerateShortTimeString();
		string ret = "" + dateStr + "-" + timeStr;
		return ret;
	}
};

static string TraderPlusTrimSpaces(string line)
{
	line.Replace("	", "");
	bool HasSpaces = true;
	while(HasSpaces)
	{
		line = line.Trim();
		if (line.Length() > 0)
			HasSpaces = line[0] == " " || line[line.Length() - 1] == " ";
		else
			HasSpaces = false;
	}
	return line;
}

/*Class that deals with the log system*/
static ref TraderPlusLogger g_TraderPlusLogger;
static TraderPlusLogger GetTraderPlusLogger(){
	if (!g_TraderPlusLogger) {
		g_TraderPlusLogger = new TraderPlusLogger();
	}
	return g_TraderPlusLogger;
}
