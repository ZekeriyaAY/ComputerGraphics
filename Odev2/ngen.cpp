#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <GL/glut.h>

const double IKI_PI = 6.2831853;

/* Başlangıç gösterim penceresi boyutu */
GLsizei pencereEni = 400, pencereBoyu = 400;
GLuint altigen;

class ekrandaNokta
{
private:
	GLint x,y;
public:
	ekrandaNokta (){
		x = y = 0;
	}
	void setKoordinat(GLint xKoord, GLint yKoord){
		x = xKoord;
		y = yKoord;
	}
	GLint getx() const{
		return x;
	}
	GLint gety() const{
		return y;
	}

};
static void init(void)
{
	ekrandaNokta altigenKose, cemberMerkez;
	GLdouble theta;
	GLint k;

	/* Çemberin merkez koordinatı ayarla */
	cemberMerkez.setKoordinat(pencereEni/2, pencereBoyu/2);

	glClearColor(1.0,1.0,1.0,0.0);		// beyaz renkte gösterim penceresi

	/* Kırmızı düzgün altıgen nesnesi için bir gösterim listesi kur.
	 * Altıgenin köşeleri bir çemberin çevresinde eşit uzaklıkta altı noktadır.
	*/
	altigen = glGenLists(1); // Gösterim listesi içn bir numara ata
	GLint N = 150;
	GLint r = 50;
	glNewList(altigen, GL_COMPILE);
		glColor3f(1.0f, 0.0f, 0.0f);			//çizgi rengini kırmızıya ata
		glBegin (GL_POLYGON);
			for(k=0; k<=N; k++){
				theta = IKI_PI*k/N;
				altigenKose.setKoordinat(cemberMerkez.getx()+r*cos(theta),cemberMerkez.gety()+r*sin(theta));
				glVertex2i(altigenKose.getx(), altigenKose.gety());
			}
		glEnd();
	glEndList();

}
void pencereYenidenSekillendir(int yeniEn, int yeniBoy){	
	glMatrixMode(GL_PROJECTION);		// projeksiyon parametrelerini ayarla
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble) yeniEn, 0, (GLdouble) yeniBoy);
	glClear(GL_COLOR_BUFFER_BIT);
}
void duzgunAltigen(void)
{
	glClear(GL_COLOR_BUFFER_BIT);         // Renk tamponunu temizle
	glCallList(altigen);
	glFlush();	//Tüm openGL süreçlerini mümkün mertebe çabuk bir şekilde işle
}

int main(int argc, char* argv[])
{
	glutInit(&argc, (char**) argv);  // GLUT'u başlat
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //gösterim modunu ayarla
	glutInitWindowPosition(100, 100); // Pencerenin sol üst ekran köşesinden uzaklığını ayarla
	glutInitWindowSize(pencereEni, pencereBoyu);   // Pencere boyunu ayarla
	glutCreateWindow("Yeniden Sekillendirme Fonksiyonu ve Gösterim Listesi Örnegi");	// Verilen başlıkla pencereyi oluştur
	init();							//İlklendirmeyi çalıştır
	glutDisplayFunc(duzgunAltigen); // Yeniden pencere çizimleri için gösterim geri bildirim fonksiyonunu kayıtla
	glutReshapeFunc(pencereYenidenSekillendir);
	
	glutMainLoop();           // Sonsuz bir şekilde süreç işlem döngüsüne gir
	return 0;
}
