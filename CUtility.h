/// <summary>
/// Summary description for Utility.
/// </summary>
class CUtility
{
public:
    static BOOL GetMediaFile( char* file, char path[] );
private:
    static BOOL SearchFolders( char* filename, char* exeFolder, char* exeName, char fullPath[] );
};