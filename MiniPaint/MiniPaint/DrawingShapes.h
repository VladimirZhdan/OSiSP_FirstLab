#ifndef __DrawingShapes__
#define __DrawingShapes__

#include <vector>
#include "DrawObject.h"

class DrawingShapes
{
public:	
	static void InitInstance(HWND hWnd);
	static DrawingShapes* getInstance();
	~DrawingShapes();
	void StartDrawing(DrawObject *shape);
	void RedrawAllShapes(HDC hdc, RECT *clientRect);
	void AddDot(POINT point);
	void Drawing(POINT point);
	void AddExtraDot();
	void AddInformation(TCHAR inf);
	bool isEndDrawing();
	void setMetaFile(HENHMETAFILE hEnhMetaFile);
	void DeleteLastShape();
	RECT* GetRectOfLastObject();
	void ChangeCoordinatesOfDrawObjects(int deltaX, int deltaY);
	void Zooming(float zoom);
	void ClearShapes();
		
private:
	DrawingShapes();
	void ChangeCoordinatesOfMetaFileRect(int deltaX, int deltaY);
	static DrawingShapes* instance;	
	std::vector<DrawObject*> shapes;
	bool endDrawing = true;
	DrawObject *currentShape;
	HWND hWnd;
	HENHMETAFILE hEnhMetaFile;
	float zoom;
	RECT deltaMetaFileRect;


};


;
#endif
