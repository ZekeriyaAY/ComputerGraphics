#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

/* Başlangıç gösterim penceresi boyutu */
GLsizei pencereEni = 600, pencereBoyu = 500;

/* Tarama konumunu ilklendir */
GLsizei xRaster = 25, yRaster = 150;
GLubyte etiket[36] = {'O','c','a',	'S','u','b',	'M','a','r',
					'N','i','s',	'M','a','y',	'H','a','z',
					'T','e','m',	'A','g','u',	'E','y','l',
					'E','k','m',	'K','a','s',	'A','r','a',};
GLint dataValue[12] = {420, 342, 324, 310, 262, 185,
						190, 196, 217, 240, 312, 438};

static void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);		// beyaz renkte gösterim penceresi
	glMatrixMode(GL_PROJECTION);		// projeksiyon parametrelerini ayarla
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 500);
}
void pencereYenidenSekillendir(int yeniEn, int yeniBoy){	
	glMatrixMode(GL_PROJECTION);		// projeksiyon parametrelerini ayarla
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble) yeniEn, 0, (GLdouble) yeniBoy);
	glClear(GL_COLOR_BUFFER_BIT);
}
void cizgiGrafigi(void)
{
	GLint ay, k;

	glClear(GL_COLOR_BUFFER_BIT); //Gösterim penceresini temizle
	glLineWidth(3.0);			//Çizgi kalınlığını ayarla
	glEnable(GL_LINE_STIPPLE);	//Çizgi özellik değişimini aktifleştir
	glColor3f(0.0f, 0.0f, 1.0f);			//çizgi rengini maviye ata
	//Veriyi kırıklı hat şeklinde çizdir
	glBegin (GL_LINE_STRIP);
		for(k=0; k<12; k++)
			glVertex2i(xRaster+5+k*50, dataValue[k]);
	glEnd();
	glDisable(GL_LINE_STIPPLE);		//Çizgi özellik değişimini inaktifleştir
	
	//Veri noktalarını yıldız şeklinde çizdir
	glColor3f(1.0f, 0.0f, 0.0f);			//işaretçi rengini kırmızıya ata
	for(k=0; k<12; k++){	
			glRasterPos2i(xRaster+k*50, dataValue[k]-4);
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
	}

	//Grafik etiketlerini çizdir
	glColor3f(0.0f, 0.0f, 0.0f);			//yazı rengini siyaha ata
	xRaster = 20;
	for(ay=0; ay<12; ay++){	
			glRasterPos2i(xRaster, yRaster);
			for(k=3*ay; k<3*ay+3; k++)	
					glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, etiket[k]);
			xRaster += 50;
	}

	glFlush();	//Tüm openGL süreçlerini mümkün mertebe çabuk bir şekilde işle
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**) argv);  // GLUT'u başlat
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //gösterim modunu ayarla
	glutInitWindowPosition(100, 100); // Pencerenin sol üst ekran köşesinden uzaklığını ayarla
	glutInitWindowSize(pencereEni, pencereBoyu);   // Pencere boyunu ayarla
	glutCreateWindow("Çizgi Grafiği Veri Çizdirimi");	// Verilen başlıkla pencereyi oluştur
	init();							//İlklendirmeyi çalıştır
	glutDisplayFunc(cizgiGrafigi); // Yeniden pencere çizimleri için gösterim geri bildirim fonksiyonunu kayıtla
	glutReshapeFunc(pencereYenidenSekillendir);
	
	glutMainLoop();           // Sonsuz bir şekilde süreç işlem döngüsüne gir
	return 0;
}